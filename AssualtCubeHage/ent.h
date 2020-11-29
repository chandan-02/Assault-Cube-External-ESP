#pragma once

#include "iostream"
#include <Windows.h>
#include "structs.h"
#include "proc.h"

class Entity
{
public:
	char name[20];
	int health = 0;
	int base = 0;
	float matrix[16];
	/*vec2d screen;*/
	vec3d headPos;
	vec3d feetPos;
	int team = 0;
};
