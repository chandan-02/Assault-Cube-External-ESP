#include "mycal.h"

#include <cmath>

bool MyMaths::worldToScreen(vec3d pos, vec3d& screen, float matrix[16], int width, int height) {
	MyMaths::clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	MyMaths::clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	MyMaths::clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	MyMaths::clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f) {
		return false;
	}

	MyMaths::NDC.x = clipCoords.x / clipCoords.w;
	MyMaths::NDC.y = clipCoords.y / clipCoords.w;
	MyMaths::NDC.z = clipCoords.z / clipCoords.w;

	MyMaths::screen.x = (width / 2 * NDC.x) + ( NDC.x + width / 2);
	MyMaths::screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);
	return true;
}

float MyMaths::getDistance3d(vec3d m_pos, vec3d en_pos) {
	return (float)(sqrt(((m_pos.x - en_pos.x) * (m_pos.x - en_pos.x)) + ((m_pos.y - en_pos.y) * (m_pos.y - en_pos.y)) + ((m_pos.z - en_pos.z) * (m_pos.z - en_pos.z))));
}