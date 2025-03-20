#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <WinUser.h>
#include <strsafe.h>
#include <stdio.h>
#include <Shlwapi.h>
#include <ntstatus.h>
#include <winternl.h>

#pragma comment(lib, "BCrypt.lib")
#pragma comment(lib, "ntdll.lib")

#define DEFAULT_OVERWRITE_SIZE 2000000

typedef struct SecureDeletorSpecialArguments {
	BOOL useDefaultSettings; // Will use the default settings. RESERVED.
	BOOL force; // 1 - Force.
	BOOL enableLogging; // 1 - Enable Logging.
	LPWSTR logPath; // Path to the log file.
	BOOL enableVerbosity; // 1 - Enable Verbosity.
	INT passes; // Number of passes to overwrite a file. [isFile should be TRUE]

} SDSPECIALARGUMENTS, *PSDSPECIALARGUMENTS;

typedef struct SecureDeletorArguments {
	LPWSTR path; // Path to the file / folder to securely delete.
	BOOL isFile; // 0 - File. 1 - Folder.
	BOOL recurse; // 0 - Full Recursion (Default). 1 - Affects only files under the parent folder. [isFile should be FALSE]
	BOOL writeMode; // 0 - Random Write (Default). 1 - Zero Write.
	BOOL shouldDelete; // 0 - Will not delete the files and directories overwritten (Default). 1 - Will delete overwritten files and directories.
	SDSPECIALARGUMENTS sdsa; // Special arguments required.
} SDARGUMENTS, *PSDARGUMENTS;

/* Special Definitions. */
typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[ANYSIZE_ARRAY];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

/* Print Definitions. */
static CONST LPWSTR helpString = L"\r\nSecureFileDeletor.exe {-file <abs_path> | -dir <abs_path>} [-default] [-force] [-log <output>] [-verbose]\r\n\r\nSecureFileDeletor.exe {-file <abs_path> | -dir <abs_path>} [-recurse1] {-rand | -zero} [-delete] [-force] [-log <output>] [-verbose] [-passes <n>]\r\n\r\nParameters:\r\n\r\n-file <abs_path> | -dir <abs_path> -> Selects a file or a directory for overwriting.\r\n";

/* Functions.c Definitions. */
extern inline VOID WINAPI PrintStringToConsole(LPWSTR string) { wprintf(string); }
VOID WINAPI SecureDeletor(PSDARGUMENTS sda);
VOID WINAPI SecureDeletorFile(PSDARGUMENTS sda);
VOID WINAPI SecureDeletorDirectory(PSDARGUMENTS sda);
VOID WINAPI SecureDeletorFileN(PSDARGUMENTS sda);
VOID WINAPI SecureDeletorDirectoryN(PSDARGUMENTS sda);
VOID WINAPI SecureDeletorRandomOverwrite(HANDLE hFile, LARGE_INTEGER fileSize);
VOID WINAPI SecureDeletorZeroOverwrite(HANDLE hFile, LARGE_INTEGER fileSize);
VOID WINAPI SecureDeletorForce(LPWSTR path);
