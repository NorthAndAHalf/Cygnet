#pragma once
#include "pch.h"
#include <vector>
#include "Primitive.h"
#include "glm/vec3.hpp"
#include "Ray.h"

class Traceable
{
public:
	
	glm::vec3 Trace(Ray& ray);
	float Intersect(Ray& ray);
	float Intersect(Ray& ray, glm::vec3& colour);

private:
	std::unique_ptr<std::vector<std::shared_ptr<Primitive>>> primitives; // Unique pointer of vector that stores shared pointers of Primitives

	/*
	Will require an acceleration structure to be stored here in the future
	The trace and intersect functions will traverse this first before touching primitives
	I assume I'll remove the primitives vector as primitive pointers will be stored in the acceleration structure instead
	Idk yet though, maybe the structure will store indices for the primitive array instead
	*/
};