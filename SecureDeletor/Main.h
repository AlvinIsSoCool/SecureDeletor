#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <WinUser.h>
#include <strsafe.h>
#include <stdio.h>

#pragma comment(lib, "BCrypt.lib")

#define DEFAULT_OVERWRITE_SIZE 2000000
#define DEFAULT_OVERWRITE_SIZE_CALCULATE(sectorSize) sectorSize * ((DEFAULT_OVERWRITE_SIZE / sectorSize) + 1)