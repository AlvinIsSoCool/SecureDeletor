#include "Main.h"

VOID WINAPI SecureDeletor(PSDARGUMENTS sda) {
	if (sda->isFile == TRUE) SecureDeletorFile(sda);
	if (sda->isFile == FALSE) SecureDeletorDirectory(sda);
}

VOID WINAPI SecureDeletorFile(PSDARGUMENTS sda) {
	SecureDeletorFileN(sda);
}

VOID WINAPI SecureDeletorDirectory(PSDARGUMENTS sda) {
	SecureDeletorDirectoryN(sda);
}

VOID WINAPI SecureDeletorFileN(PSDARGUMENTS sda) {
	SDARGUMENTS sda1 = *sda;

	HANDLE hFile = CreateFile(sda1.path, GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
	if (GetLastError() == ERROR_ACCESS_DENIED && sda1.sdsa.force) {
		if (sda1.sdsa.enableVerbosity) wprintf(L"[VERBOSE]: CreateFile(...) failed. Attempting unforceful fixes...");
		SetFileAttributes(sda1.path, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
		hFile = CreateFile(sda1.path, GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
		if ((hFile == NULL || hFile == INVALID_HANDLE_VALUE) && sda1.sdsa.force) {
			if (sda1.sdsa.enableVerbosity) wprintf(L"[VERBOSE]: -force specified. Attempting forceful file open...");
			SecureDeletorForce(sda1.path);
		}
		else if (!sda1.sdsa.force) wprintf(L"-force unspecified. Operation Failed. Specify -force and try again, if needed.");
	}
	if (sda1.sdsa.enableVerbosity) wprintf(L"[VERBOSE]: File: %s Opened.", sda1.path);
	LARGE_INTEGER fileSize;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&fileSize, sizeof(fileSize));
	ZeroMemory(&mbi, sizeof(mbi));
	GetFileSizeEx(hFile, &fileSize);

	if (sda1.writeMode == 0) {
		if (sda1.sdsa.enableVerbosity) wprintf(L"[VERBOSE]: Random Overwrite Specified. Proceeding...");
		for (INT i = 0; i < sda1.sdsa.passes; i++) SecureDeletorRandomOverwrite(hFile, fileSize);
	}
	else if (sda1.writeMode == 1) {
		if (sda1.sdsa.enableVerbosity) wprintf(L"[VERBOSE]: Zero Overwrite Specified. Proceeding...");
		for (INT i = 0; i < sda1.sdsa.passes; i++) SecureDeletorZeroOverwrite(hFile, fileSize);
	}

	if (sda1.shouldDelete == 1) {
		DeleteFile(sda1.path);
		wprintf(L"File: %s overwritten and deleted.", sda1.path);
	}
	wprintf(L"File: %s overwritten", sda1.path);
}

VOID WINAPI SecureDeletorDirectoryN(PSDARGUMENTS sda) {
	SDARGUMENTS sda1 = *sda;

	wprintf(L"Directory Not Handled Yet!");
}

VOID WINAPI SecureDeletorRandomOverwrite(HANDLE hFile, LARGE_INTEGER fileSize) {
	DWORD bytesWritten = 0;
	PBYTE randomData = 0;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));

	if (fileSize.QuadPart < DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, fileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		if (BCryptGenRandom(NULL, randomData, mbi.RegionSize, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != STATUS_SUCCESS) wprintf(L"[WARN]: Random Overwrite Failed. Falling Back To Zero Overwrite.");
		WriteFile(hFile, randomData, mbi.RegionSize, &bytesWritten, NULL);
	}

	if (fileSize.QuadPart >= DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, DEFAULT_OVERWRITE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		for (INT i = 0; i < ((fileSize.QuadPart / mbi.RegionSize) + 1); i++) {
			if (BCryptGenRandom(NULL, randomData, mbi.RegionSize, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != STATUS_SUCCESS) wprintf(L"[WARN; WRITE_%d%]: Random Overwrite Failed. Falling Back To Zero Overwrite.", i);
			WriteFile(hFile, randomData, mbi.RegionSize, &bytesWritten, NULL);
		}
	}
	VirtualFree(randomData, 0, MEM_RELEASE);
}

VOID WINAPI SecureDeletorZeroOverwrite(HANDLE hFile, LARGE_INTEGER fileSize) {
	DWORD bytesWritten = 0;
	PBYTE randomData = 0;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));

	if (fileSize.QuadPart < DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, fileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		WriteFile(hFile, randomData, mbi.RegionSize, &bytesWritten, NULL);
	}

	if (fileSize.QuadPart >= DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, DEFAULT_OVERWRITE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		for (INT i = 0; i < ((fileSize.QuadPart / mbi.RegionSize) + 1); i++) {
			WriteFile(hFile, randomData, mbi.RegionSize, &bytesWritten, NULL);
		}
	}
	VirtualFree(randomData, 0, MEM_RELEASE);
}

VOID WINAPI SecureDeletorForce(LPWSTR path) {
	HANDLE hToken = 0;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);

	PTOKEN_PRIVILEGES tokenPriv = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TOKEN_PRIVILEGES) + sizeof(LUID_AND_ATTRIBUTES[4]));

	tokenPriv->PrivilegeCount = 5;
	LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &tokenPriv->Privileges[0].Luid);
	tokenPriv->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	LookupPrivilegeValue(NULL, SE_RESTORE_NAME, &tokenPriv->Privileges[1].Luid);
	tokenPriv->Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tokenPriv->Privileges[2].Luid);
	tokenPriv->Privileges[2].Attributes = SE_PRIVILEGE_ENABLED;
	LookupPrivilegeValue(NULL, SE_SECURITY_NAME, &tokenPriv->Privileges[3].Luid);
	tokenPriv->Privileges[3].Attributes = SE_PRIVILEGE_ENABLED;
	LookupPrivilegeValue(NULL, SE_TAKE_OWNERSHIP_NAME, &tokenPriv->Privileges[4].Luid);
	tokenPriv->Privileges[4].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, tokenPriv, 0, NULL, 0)) wprintf(L"Token privileges could not be set. Proceeding without...");

	HeapFree(GetProcessHeap(), 0, tokenPriv);
	CloseHandle(hToken);

	ForceStopProcesses();
}

VOID WINAPI ForceStopProcesses() {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	HANDLE hProcess = 0;

	PROCESSENTRY32W pe32w = { 0 };
	pe32w.dwSize = sizeof(PROCESSENTRY32W);

	LPWSTR cModuleName = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, WMAX_PATH + 1);
	GetModuleFileName(NULL, cModuleName, WMAX_PATH);

	Process32First(hSnapshot, &pe32w);

	BOOL criticalProcess = FALSE;
	while (Process32Next(hSnapshot, &pe32w)) {
		for (INT x = 0; x < procWhitelistSize; x++) {
			if (lstrcmp(pe32w.szExeFile, procWhitelist[x]) != 0 && lstrcmp(pe32w.szExeFile, cModuleName) != 0) criticalProcess = FALSE;
			else {
				criticalProcess = TRUE;
				break;
			}
		}
		if (!criticalProcess) {
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32w.th32ProcessID);
			TerminateProcess(hProcess, 0);
		}
	}
}