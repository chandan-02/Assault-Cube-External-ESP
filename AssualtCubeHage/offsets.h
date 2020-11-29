#pragma once

#include <vector>

#define playerBase 0x010f4f4;
#define playersInMap 0x010F500;
#define entityBase 0x010F4F8;
#define viewMatrix 0x501AE8;
#define widthOffset 0x110C94;
#define heightOffset 0x110C98;

std::vector<unsigned int> healthOffset = { 0xF8 };
std::vector<unsigned int> ammoOffset = { 0x374,0x14,0x0 };
std::vector<unsigned int> nameOffset = { 0x225 };
std::vector<unsigned int> posx = { 0x4};
std::vector<unsigned int> posy = { 0x8 };
std::vector<unsigned int> posz = { 0xC };

std::vector<unsigned int> angleHorizontal = { 0x40 };
std::vector<unsigned int> angleVertical = { 0x44 };
std::vector<unsigned int> team = { 0x32C };
//std::vector<unsigned int> viewMatrix = { 0x501AE8 };
std::vector<unsigned int> posxNormal = { 0x34 };
std::vector<unsigned int> posyNormal = { 0x38 };
std::vector<unsigned int> poszNormal = { 0x3C };



