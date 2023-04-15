#pragma once
#include "Ray.h"

struct AABB
{
	AABB(float _minX, float _maxX, float _minY, float _maxY, float _minZ, float _maxZ);

	bool Intersect(const Ray& ray);

	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
};