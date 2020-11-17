#pragma once

#include <iostream>
#include <Windows.h>
#include "structs.h"
//#include "offsets.h"
#include "proc.h"

class Player
{
	public:
		char name[20];
		int health=0;
		float matrix[16];
		vec3d screen;
		vec3d headPos;
		vec3d feetPos;
		int teamC=0;

		void getInfoPlayer();
		void printDebug();
};

