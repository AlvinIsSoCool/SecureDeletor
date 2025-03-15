#include "Main.h"

INT __cdecl main(VOID) {
	// TODO: Make this a command-Line app as well.
	//PrintStringToConsole(helpString, lstrlen(helpString));
	INT argc = 0;
	LPWSTR commandLine = GetCommandLine();
	LPWSTR* argv = CommandLineToArgvW(commandLine, &argc);
	SDARGUMENTS sda;
	ZeroMemory(&sda, sizeof(sda));
	DWORD attr;
	INT i = 0;

	if (lstrcmp(argv[1], L"-file") == 0) {
		attr = GetFileAttributes(argv[2]);
		if (GetLastError() == ERROR_FILE_NOT_FOUND) wprintf(L"Invalid File!");
		else if (attr & FILE_ATTRIBUTE_DIRECTORY) wprintf(L"Not a file!");
		else {
			sda.path = argv[2];
			sda.isFile = TRUE;
		}
	}
	if (lstrcmp(argv[1], L"-dir") == 0) {
		GetFileAttributes(argv[2]);
		if (GetLastError() == ERROR_PATH_NOT_FOUND) wprintf(L"Invalid directory!");
		else if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) wprintf(L"Not a directory!");
		else {
			sda.path = argv[2];
			sda.isFile = FALSE;
		}
	}

	if (lstrcmp(argv[3], L"-default") == 0) {
		sda.recurse = sda.writeMode = sda.shouldDelete = 0;
		sda.sdsa.passes = 1;
	}

	if (lstrcmp(argv[3], L"-recurse1") == 0 && sda.isFile == FALSE) sda.recurse = 1;
	else if (lstrcmp(argv[3], L"-recurse1") == 0 && sda.isFile == TRUE) wprintf(L"Invalid Arguments / Argument Combination! -recurse1 cannot be used with a -file.");
	else if (lstrcmp(argv[3], L"-recurse1") != 0 && sda.isFile == FALSE) sda.recurse = 0;
	else wprintf(L"Invalid Arguments!");

	i = (sda.recurse == 1 || sda.sdsa.useDefaultSettings == 1) ? 3 : 4;

	if (lstrcmp(argv[i], L"-rand") == 0) sda.writeMode = 0;
	else if (lstrcmp(argv[i], L"-zero") == 0) sda.writeMode = 1;
	else wprintf(L"Invalid Arguments!");

	if (lstrcmp(argv[i + 1], L"-delete") == 0) sda.shouldDelete = 1;

	for (INT x = i + 1; x < argc; x++) {
		if (lstrcmp(argv[x], L"-force") == 0) sda.sdsa.force;
		if (lstrcmp(argv[x], L"-log") == 0) {
			sda.sdsa.enableLogging = 1;
			sda.sdsa.logPath = argv[x + 1];
		}
		if (lstrcmp(argv[x], L"-verbose") == 0) sda.sdsa.enableVerbosity = 1;
		if (lstrcmp(argv[x], L"-passes") == 0) sda.sdsa.passes = StrToInt(argv[x + 1]);
	}



	//PrintStringToConsole(commandLine, lstrlen(commandLine));
	//MessageBox(NULL, commandLine, "SecureDeletor.exe", MB_OK);
	/* RANDOM OVERWRITE */
	/*LPWSTR overwriteFilename = L"S:\\sfd test\\Test File.mp4";
	HANDLE file = CreateFile(overwriteFilename, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
	LARGE_INTEGER fileSize;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&fileSize, sizeof(fileSize));
	ZeroMemory(&mbi, sizeof(mbi));
	GetFileSizeEx(file, &fileSize);
	DWORD bytesWritten = 0;
	PBYTE randomData = 0;
	
	if (fileSize.QuadPart < DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, fileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		BCryptGenRandom(NULL, randomData, mbi.RegionSize, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
		WriteFile(file, randomData, mbi.RegionSize, &bytesWritten, NULL);
	}

	if (fileSize.QuadPart >= DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, DEFAULT_OVERWRITE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		for (INT i = 0; i < ((fileSize.QuadPart / mbi.RegionSize) + 1); i++) {
			BCryptGenRandom(NULL, randomData, mbi.RegionSize, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
			WriteFile(file, randomData, mbi.RegionSize, &bytesWritten, NULL);
		}
	}
	VirtualFree(randomData, 0, MEM_RELEASE); */

	/* ZERO OVERWRITE */
	/*LPWSTR overwriteFilename = L"S:\\sfd test\\Test File.mp4";
	HANDLE file = CreateFile(overwriteFilename, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
	LARGE_INTEGER fileSize;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&fileSize, sizeof(fileSize));
	ZeroMemory(&mbi, sizeof(mbi));
	GetFileSizeEx(file, &fileSize);
	DWORD bytesWritten = 0;
	PBYTE randomData = 0;

	if (fileSize.QuadPart < DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, fileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		WriteFile(file, randomData, mbi.RegionSize, &bytesWritten, NULL);
	}

	if (fileSize.QuadPart >= DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, DEFAULT_OVERWRITE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		for (INT i = 0; i < ((fileSize.QuadPart / mbi.RegionSize) + 1); i++) {
			WriteFile(file, randomData, mbi.RegionSize, &bytesWritten, NULL);
		}
	}
	VirtualFree(randomData, 0, MEM_RELEASE); */
}