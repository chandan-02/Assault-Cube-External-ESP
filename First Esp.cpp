#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

//DOCs:
//Step 1  : Get Proccess Id of the Target Addresss (Here our Game)
//getProcId("ac_client.exe");
//std::cout << "Hello World !";
//Step 2  : Getmodulebaseaddress - this will tell us base address of .exe in the memory (Here base Address of Game.exe).
//Step 3  : Getting a Handle to the process (For reading and wrting from memory and drawing esp and manuplating other variables of game.exe )

int main()
{
    DWORD procId = getProcId(L"ac_client.exe");
    uintptr_t moduleBase = getModuleBaseAddress(procId, L"ac_client.exe");
    
    HANDLE hProc = 0; //0 for Error checking latter in future.
    hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
 
    uintptr_t dynamicBaseAddress = moduleBase + 0x10F4f4; //mainbase to work from
    std::cout << std::hex << dynamicBaseAddress << std::endl ;

    std::vector<unsigned int> AmmoOffset = {0x374,0x14,0x0}; //Resole of ammo pointer chain.
    std::vector<unsigned int> HealthOffset = { 0xF8 }; //Resole of health pointer chain.

    uintptr_t ammoAddr = findDMAAddy(hProc, dynamicBaseAddress, AmmoOffset);
    uintptr_t healthAddr = findDMAAddy(hProc, dynamicBaseAddress, HealthOffset);

    //Read ammo 
    int ammoValue = 0;
    ReadProcessMemory(hProc, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), 0);
    std::cout << std::dec << ammoValue;
    //write ammo
    int editAmmo = 999;
    WriteProcessMemory(hProc, (BYTE*)ammoAddr, &editAmmo, sizeof(editAmmo), 0);


    //Read Health 
    int healthValue = 0;
    ReadProcessMemory(hProc, (BYTE*)healthAddr, &healthValue, sizeof(ammoValue), 0);
    std::cout << std::dec << ammoValue;
    //write Health
    int editHelth = 999;
    WriteProcessMemory(hProc, (BYTE*)healthAddr, &editHelth, sizeof(editAmmo), 0);
}

