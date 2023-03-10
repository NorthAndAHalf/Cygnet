#pragma once
#include "pch.h"
#include "Ray.h"

class Primitive
{
public:
	virtual glm::vec3 Trace(Ray& ray) = 0;
	virtual float Intersect(Ray& ray) = 0;
	virtual float Intersect(Ray& ray, glm::vec3& colour) = 0;
};