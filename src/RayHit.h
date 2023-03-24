#pragma once
#include "glm/vec3.hpp"
#include "Material.h"

struct RayHit
{
	RayHit(glm::vec3 _pos, glm::vec3 _rayDir, glm::vec3 _normal, Material _mat, float _t, glm::vec3 _outColour);

	glm::vec3 pos;
	glm::vec3 rayDir;
	glm::vec3 normal;
	Material mat;
	float t;
	glm::vec3 outColour;
};
