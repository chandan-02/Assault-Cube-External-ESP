#include "ent.h"

void Entity::printDebug() {
	std::cout << "Name of player is  : " << name ;
	std::cout << "HeadPosition : " << headPos.x << " " <<headPos.y <<" " << headPos.z <<std::endl;
	std::cout << "FeetPosition : " << feetPos.x << " " << feetPos.y << " " << feetPos.z <<std::endl;
	std::cout << "Team : " << team<< std::endl;
	std::cout << "\n\n";
}
