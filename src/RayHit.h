#pragma once
#include "glm/vec3.hpp"
#include "Material.h"
#include "Ray.h"
#include "BRDF/BRDF.h"
#include <memory>

struct RayHit
{
	RayHit(Ray _ray, glm::vec3 _pos, glm::vec3 _normal, std::shared_ptr<Material> _mat, float _t);
	RayHit();

	Ray ray;
	glm::vec3 pos;
	glm::vec3 normal;
	std::shared_ptr<Material> mat;
	float t;
	bool miss;
};
