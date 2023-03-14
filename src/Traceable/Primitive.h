#pragma once
#include "pch.h"
#include "Ray.h"
#include "RayHit.h"

class Primitive
{
public:
	virtual RayHit Trace(Ray& ray, uint8_t depth) = 0;
	virtual float Intersect(Ray& ray, glm::vec3& normal) = 0;
	virtual float Intersect(Ray& ray, glm::vec3& colour, glm::vec3& normal) = 0;
};