#include <iostream>
#include <vector>
#include "proc.h"

//int mains()
//{
//	DWORD procId = getProcId(L"ac_client.exe");
//	uintptr_t modAddr = getModuleBaseAddr(procId, L"ac_client.exe");
//	uintptr_t modBase = modAddr + 0x010F4F4;
//	HANDLE hProc = 0;
//	hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
//
//	std::cout << "AC CLient Base Address : " << modBase << std::endl;
//	std::vector<unsigned int> health = { 0xF8 };
//	std::vector<unsigned int> Ammo = { 0x374, 0x14, 0x0 };
//	
//	uintptr_t healthAddr = FindDMAAddy(hProc, modBase, health);
//	uintptr_t AmmoAddr = FindDMAAddy(hProc, modBase, Ammo);
//	int ehealth = 1001;
//	int eAmmo = 1009;
//	WriteProcessMemory(hProc, (BYTE*)healthAddr, &ehealth, sizeof(ehealth), 0);
//	WriteProcessMemory(hProc, (BYTE*)AmmoAddr, &eAmmo, sizeof(eAmmo), 0);
//
//	/*std::vector<unsigned int> x = { 0x04 };
//	std::vector<unsigned int> y = { 0x08 };
//	std::vector<unsigned int> z = { 0x0C };
//
//	uintptr_t xAddr = FindDMAAddy(hProc, modBase, x);
//	uintptr_t yAddr = FindDMAAddy(hProc, modBase, y);
//	uintptr_t zAddr = FindDMAAddy(hProc, modBase, z);
//	int xC = 0;
//	int yC = 0;
//	int zC = 0;
//	while (true) {
//		ReadProcessMemory(hProc, (BYTE*)xAddr, &xC, sizeof(xC), nullptr);
//		std::cout << "X-Coord :" << xC << std::endl;
//		ReadProcessMemory(hProc, (BYTE*)xAddr, &yC, sizeof(yC), nullptr);
//		std::cout << "Y-Coord :" << yC << std::endl;
//		ReadProcessMemory(hProc, (BYTE*)xAddr, &zC, sizeof(zC), nullptr);
//		std::cout << "Z-Coord :" << zC << std::endl;
//		
//	}*/
//	
//}

int main() {
	uintptr_t modBaseAddr = 0, playerEnt = 0, healthA = 0,ammoA=0;
	HANDLE hProc = 0;
	DWORD procId = getProcId(L"ac_client.exe");

	if (procId) {
		std::cout << "Process Found !" << std::endl;
		std::cout << "+++++++++++++++" << std::endl;
		std::cout << "1. Increase Health" << std::endl;
		std::cout << "2. Dec Health" << std::endl;
		std::cout << "3. Shoot Normally to Increase Ammo" << std::endl;
		std::cout << "4. Dec Ammo to deafult " << std::endl;

		hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
		modBaseAddr = getModuleBaseAddr(procId,L"ac_client.exe");
		playerEnt = modBaseAddr + 0x010F4F4;
		healthA = FindDMAAddy(hProc, playerEnt, { 0xF8 });
		ammoA = FindDMAAddy(hProc, playerEnt, { 0x374,0x14,0x0 });
	}
	else {
		std::cout << "Process not found !";
	}

	DWORD dwexit = 0;
	while (GetExitCodeProcess(hProc,&dwexit) && dwexit == STILL_ACTIVE) {
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			int eHealth = 0;
			ReadProcessMemory(hProc, (BYTE*)healthA,&eHealth , sizeof(eHealth), 0);
			eHealth = eHealth+100;
			WriteProcessMemory(hProc, (BYTE*)healthA, &eHealth, sizeof(eHealth), 0);
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
			int eHealth = 0;
			ReadProcessMemory(hProc, (BYTE*)healthA, &eHealth, sizeof(eHealth), 0);
			eHealth--;
			WriteProcessMemory(hProc, (BYTE*)healthA, &eHealth, sizeof(eHealth), 0);
		}
		if (GetAsyncKeyState(VK_LBUTTON) & 1) {
			int eAmmo = 0;
			ReadProcessMemory(hProc, (BYTE*)ammoA, &eAmmo, sizeof(eAmmo), 0);
			eAmmo++;
			WriteProcessMemory(hProc, (BYTE*)ammoA, &eAmmo, sizeof(eAmmo), 0);
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
			int eAmmo = 0;
			ReadProcessMemory(hProc, (BYTE*)ammoA, &eAmmo, sizeof(eAmmo), 0);
			eAmmo = 20;
			WriteProcessMemory(hProc, (BYTE*)ammoA, &eAmmo, sizeof(eAmmo), 0);
		}
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			return 0;
		}
	}
}
 
