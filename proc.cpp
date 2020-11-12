#include "proc.h"
//DOCS AND EXPLANATIONS HERE.
//(1)
//HANDLE is basically trying ot get a snap(list in ez words) of all running process.
//(2) // same goes of module {Module : Module is basically all the .dll's attached to the game.exe }
//PROCESSENTRY32 is a structure 
//We use that struct to define a new object procEntry which hold all the details regarding the current process
//exmaple its Name, its PID,its dwsize ,etc (From DOCs) .The function Process32First might fail if its dwsize is not mentioned.
//dwsize is basicaaly the size of varible which it will take in memory.
//define always it as sizeof(PROCESSENRTY32) then go on;
//procEntry holds the curent process and changes after Process32Next.
//(3)
//_wcsicmp("firstWideChar","SecondWideChar") is wide char string compare.

DWORD getProcId(const wchar_t* procName) {
	DWORD procId = 0;
	//Create a Snapshot basically a list of All process running in Backgorund (1)
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry; // Defining a new Structure for procEntry See(2)
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(hSnap,&procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, procName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* modName) {
	uintptr_t modBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE){
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap,&modEntry)) {
			do {
				if (!_wcsicmp(modEntry.szModule,modName)) {
					//modBaseAddr(defined in DOCs) is (byte *) inorder to be compaitable we have to typecast it to unintptr_t.
					//modBaseAddress is my defined variable of type uintptr_t;
					modBaseAddress = (uintptr_t)modEntry.modBaseAddr;
					break;	
				}
			}while(Module32Next(hSnap,&modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddress;
}
uintptr_t findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size() ; ++i ) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr),0); 
		//(ProcessHandle,in(a pointer to the base address from which to read) , (out) where to store, how to read ,error checking )	
		addr += offsets[i];
	}
	return addr;
}