#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

DWORD getProcId(const wchar_t* procName);

uintptr_t getModuleBaseAddr(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t addr, std::vector<unsigned int> offsets);

