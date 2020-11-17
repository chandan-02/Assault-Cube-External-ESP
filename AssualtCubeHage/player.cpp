#include "player.h"
#include "offsets.h"	

void Player::getInfoPlayer(){
	DWORD getProc = getProcId(L"ac_client.exe");
	uintptr_t getModuleBase = getModuleBaseAddr(getProc, L"ac_client.exe");
	uintptr_t playerBaseAddr = getModuleBase +  playerBase;

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, getProc);

	uintptr_t nameAddr = FindDMAAddy(hProc, playerBaseAddr, nameOffset);
	uintptr_t healthAddr = FindDMAAddy(hProc, playerBaseAddr, healthOffset);
	uintptr_t teamAddr = FindDMAAddy(hProc, playerBaseAddr, team);
	uintptr_t viewMatrixA =  viewMatrix;
	
	uintptr_t x = FindDMAAddy(hProc, playerBaseAddr, posx);
	uintptr_t y = FindDMAAddy(hProc, playerBaseAddr, posy);
	uintptr_t z = FindDMAAddy(hProc, playerBaseAddr, posz);

	uintptr_t xN = FindDMAAddy(hProc, playerBaseAddr, posxNormal);
	uintptr_t yN = FindDMAAddy(hProc, playerBaseAddr, posyNormal);
	uintptr_t zN = FindDMAAddy(hProc, playerBaseAddr, poszNormal);

	ReadProcessMemory(hProc, (BYTE*)nameAddr, &name, sizeof(name), nullptr);
	ReadProcessMemory(hProc, (BYTE*)healthAddr, &health, sizeof(health), nullptr);
	ReadProcessMemory(hProc, (BYTE*)teamAddr, &teamC, sizeof(teamC), nullptr);
	ReadProcessMemory(hProc, (BYTE*)viewMatrixA, &matrix, sizeof(matrix), nullptr);
	
	ReadProcessMemory(hProc, (BYTE*)x, &headPos.x, sizeof(headPos.x), nullptr);
	ReadProcessMemory(hProc, (BYTE*)y, &headPos.y, sizeof(headPos.y), nullptr);
	ReadProcessMemory(hProc, (BYTE*)z, &headPos.z, sizeof(headPos.z), nullptr);

	ReadProcessMemory(hProc, (BYTE*)xN, &feetPos.x, sizeof(feetPos.x), nullptr);
	ReadProcessMemory(hProc, (BYTE*)yN, &feetPos.y, sizeof(feetPos.y), nullptr);
	ReadProcessMemory(hProc, (BYTE*)zN, &feetPos.z, sizeof(feetPos.z), nullptr);
	
}

void Player::printDebug() {
	std::cout << "Name of Player is : "<<name << std::endl ;
	std::cout << "health of Player is : " << health << std::endl;
	std::cout << "My team is : " << teamC << std::endl;
	
	
	std::cout << "X : " << headPos.x << std::endl;
	std::cout << "Y : " << headPos.y << std::endl;
	std::cout << "Z : " << headPos.z << std::endl;

	std::cout << "XNormal : " << feetPos.x << std::endl;
	std::cout << "YNormal : " << feetPos.y << std::endl;
	std::cout << "ZNormal : " << feetPos.z << std::endl;
}