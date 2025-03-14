#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <WinUser.h>
#include <strsafe.h>
#include <stdio.h>

#pragma comment(lib, "BCrypt.lib")

#define DEFAULT_OVERWRITE_SIZE 2000000

/* Print Definitions. */
static CONST LPWSTR helpString = L"\r\nSecureFileDeletor.exe {-file <abs_path> | -dir <abs_path>} [-default] [-force] [-log <output>] [-verbose]\r\n\r\nSecureFileDeletor.exe {-file <abs_path> | -dir <abs_path>} [-recurse1] {-rand | -zero} [-delete] [-force] [-log <output>] [-verbose] [-passes <n>]\r\n\r\nParameters:\r\n\r\n-file <abs_path> | -dir <abs_path> -> Selects a file or a directory for overwriting.\r\n";

/* Functions.c Definitions. */
extern inline VOID WINAPI PrintStringToConsole(LPWSTR string) { wprintf(string); }
VOID WINAPI SecureDeletorFile(LPWSTR path, LPWSTR* argv, INT argc);
VOID WINAPI SecureDeletorDirectory(LPWSTR path, LPWSTR* argv, INT argc);