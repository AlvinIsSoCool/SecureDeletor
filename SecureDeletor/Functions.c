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

	HANDLE hFile = CreateFile(sda1.path, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_WRITE_THROUGH, NULL);
	LARGE_INTEGER fileSize;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&fileSize, sizeof(fileSize));
	ZeroMemory(&mbi, sizeof(mbi));
	GetFileSizeEx(hFile, &fileSize);

	if (sda1.writeMode == 0) {
		for (INT i = 0; i < sda1.sdsa.passes; i++) SecureDeletorRandomOverwrite(hFile, fileSize);
	}
	else if (sda1.writeMode == 1) {
		for (INT i = 0; i < sda1.sdsa.passes; i++) SecureDeletorZeroOverwrite(hFile, fileSize);
	}

	if (sda1.shouldDelete == 1) DeleteFile(sda1.path);
}

VOID WINAPI SecureDeletorDirectoryN(PSDARGUMENTS sda) {
	SDARGUMENTS sda1 = *sda;

	printf("Directory Not Handled Yet!");
}

VOID WINAPI SecureDeletorRandomOverwrite(HANDLE hFile, LARGE_INTEGER fileSize) {
	DWORD bytesWritten = 0;
	PBYTE randomData = 0;
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));

	if (fileSize.QuadPart < DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, fileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		BCryptGenRandom(NULL, randomData, mbi.RegionSize, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
		WriteFile(hFile, randomData, mbi.RegionSize, &bytesWritten, NULL);
	}

	if (fileSize.QuadPart >= DEFAULT_OVERWRITE_SIZE) {
		randomData = VirtualAlloc(NULL, DEFAULT_OVERWRITE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		VirtualQuery(randomData, &mbi, sizeof(mbi));
		for (INT i = 0; i < ((fileSize.QuadPart / mbi.RegionSize) + 1); i++) {
			BCryptGenRandom(NULL, randomData, mbi.RegionSize, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
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