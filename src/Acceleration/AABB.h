#pragma once
#include "Ray.h"
#include <vector>
#include "Traceable/Primitive.h"

struct AABB
{
	AABB(std::vector<Primitive*>* primitives);

	bool Intersect(const Ray& ray);

	glm::vec3 min;
	glm::vec3 max;
};