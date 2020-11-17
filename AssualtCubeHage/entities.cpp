#include "entities.h"
//#include "offsets.h"

void Entities::getInfoEntity() {
	uintptr_t amountBase = 0, modBase = 0;

	DWORD procId = getProcId(L"ac_client.exe");
	modBase = getModuleBaseAddr(procId, L"ac_client.exe");

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t entBase = modBase + 0x10F4F8;

	amountBase = modBase + 0x010F500;

	ReadProcessMemory(hProc, (BYTE*)amountBase, &amount, sizeof(amount), nullptr);

	list.resize(amount);
	for (int i = 1; i < amount; i++) {
		ReadProcessMemory(hProc, LPCVOID(entBase), &list[i].base, sizeof(list[i].base), nullptr);
		ReadProcessMemory(hProc, LPCVOID(list[i].base + (0x4 * i )), &list[i].base, sizeof(list[i].base), nullptr);
		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x225), &list[i].name, sizeof(list[i].name), nullptr);

		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x4), &list[i].headPos.x, sizeof(list[i].headPos.x), nullptr);
		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x8), &list[i].headPos.y, sizeof(list[i].headPos.y), nullptr);
		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0xC), &list[i].headPos.z, sizeof(list[i].headPos.z), nullptr);

		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x34), &list[i].feetPos.x, sizeof(list[i].feetPos.x), nullptr);
		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x38), &list[i].feetPos.y, sizeof(list[i].feetPos.y), nullptr);
		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x3C), &list[i].feetPos.z, sizeof(list[i].feetPos.z), nullptr);

		ReadProcessMemory(hProc, LPCVOID(list[i].base + 0x32C), &list[i].team, sizeof(list[i].team), nullptr);
	}
	
}

void Entities::printDebug() {
	std::cout << "TOTAL PLAYES IM MAP : " << amount << std::endl;
	for (int i = 1; i < amount; i++) {
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "Enemey name is :" << list[i].name<<std::endl;
		std::cout << "               " << "X :     " << "Y:      " << "Z:      "<<std::endl;
		std::cout << "HeadPosition : " << list[i].headPos.x << " " << list[i].headPos.y << " " << list[i].headPos.z << std::endl;
		std::cout << "FeetPosition : " << list[i].feetPos.x << " " << list[i].feetPos.y << " " << list[i].feetPos.z << std::endl;
		std::cout << "Team : " << list[i].team << std::endl;
		std::cout << "\n\n";
	}
}