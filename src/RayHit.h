#pragma once
#include "glm/vec3.hpp"

struct RayHit
{
	RayHit(glm::vec3 _pos, glm::vec3 _incident, glm::vec3 _normal, glm::vec3 _surface, float _emissive, float _t, int _depth);
	RayHit();

	glm::vec3 pos;
	glm::vec3 incident;
	glm::vec3 normal;
	glm::vec3 surface; // Surface colour contribution
	float emissive; // emissive light intensity (0 for not emissive)
	float t;
	int depth; // resursion depth
};