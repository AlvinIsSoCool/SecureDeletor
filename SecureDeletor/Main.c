#include "Main.h"

INT __cdecl main(VOID) {
	// TODO: Make this a command-Line app as well.
	//PrintStringToConsole(helpString, lstrlen(helpString));
	INT argc = 0;
	LPWSTR commandLine = GetCommandLine();
	LPWSTR* argv = CommandLineToArgvW(commandLine, &argc);
	LPWSTR path = L"";
	DWORD attr;
	for (INT i = 1; i < argc; i++) {
		if (lstrcmp(argv[i], L"-file") == 0) {
			attr = GetFileAttributes(argv[i + 1]);
			if (GetLastError() == ERROR_FILE_NOT_FOUND) MessageBox(NULL, L"Invalid File!", L"SecureDeletor.exe", MB_OK);
			else if (attr & FILE_ATTRIBUTE_DIRECTORY) MessageBox(NULL, L"Not a file!", L"SecureDeletor.exe", MB_OK);
			else {
				path = argv[i + i];
				SecureDeletorFile(path, argv, argc);
			}
		}
		if (lstrcmp(argv[i], L"-dir") == 0) {
			GetFileAttributes(argv[i + 1]);
			if (GetLastError() == ERROR_PATH_NOT_FOUND) MessageBox(NULL, L"Invalid directory!", L"SecureDeletor.exe", MB_OK);
			else if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) MessageBox(NULL, L"Not a directory!", L"SecureDeletor.exe", MB_OK);
			else {
				path = argv[i + i];
				SecureDeletorDirectory(path);
			}
		}
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