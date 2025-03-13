#include "Main.h"

INT
__cdecl
main(
	VOID
) {
	// TODO: Make this a command-Line app as well.
	
	/* RANDOM OVERWRITE */
	/*LPSTR overwriteFilename = "S:\\sfd test\\Test File.mp4";
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
	/*LPSTR overwriteFilename = "S:\\sfd test\\Test File.mp4";
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