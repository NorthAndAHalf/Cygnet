#pragma once
#include "glm/vec3.hpp"
#include "Material.h"
#include "Ray.h"
#include "BRDF/BRDF.h"

struct RayHit
{
	RayHit(Ray _ray, glm::vec3 _pos, glm::vec3 _normal, Material _mat, float _t);
	RayHit();

	glm::vec3 BRDFCalculate() const;

	Ray ray;
	glm::vec3 pos;
	glm::vec3 normal;
	Material mat;
	float t;
};
