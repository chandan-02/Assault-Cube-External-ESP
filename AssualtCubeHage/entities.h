#pragma once

#include "iostream"
#include <Windows.h>
#include <vector>
#include "structs.h"
#include "proc.h"
#include "ent.h"

class Entities
{
	public:
		int amount = 0;
		std::vector<Entity> list{ amount };

		void getInfoEntity();
		void printDebug();
};

