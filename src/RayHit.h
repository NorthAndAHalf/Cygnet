#pragma once
#include "glm/vec3.hpp"
#include "Material.h"
#include "Ray.h"

struct RayHit
{
	RayHit(Ray _ray, glm::vec3 _pos, glm::vec3 _normal, Material _mat, float _t);
	RayHit();

	Ray ray;
	glm::vec3 pos;
	glm::vec3 normal;
	Material mat;
	float t;
};
