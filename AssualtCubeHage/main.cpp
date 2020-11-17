#include <iostream>
//#include "offsets.h"
#include "player.h"
#include "entities.h"
#include "draw.h"
#include "mycal.h"

int main() {
	Player Me;
	Entities ent;
	Draw sense;
	MyMaths myCal{};

	Me.getInfoPlayer();
	Me.printDebug();
	ent.getInfoEntity();
	ent.printDebug();
	
	
	sense.targetWindow = FindWindow(NULL, L"AssaultCube");
	sense.hDesktop = GetDC(sense.targetWindow);
	sense.setupDrawing(sense.hDesktop, sense.targetWindow);
	sense.esp(ent, Me, myCal);
	return 0;
}

 
