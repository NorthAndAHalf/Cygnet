#pragma once
#include "pch.h"
#include <vector>
#include "Primitive.h"
#include "glm/vec3.hpp"
#include "Ray.h"

class Traceable
{
public:
	Traceable();
	~Traceable();

	RayHit Trace(Ray& ray, std::vector<Traceable*>& traceables, uint8_t depth);
	float Intersect(Ray& ray);

	void AddPrimitive(Primitive* p);

private:
	std::vector<Primitive*>* primitives; 

	/*
	Will require an acceleration structure to be stored here in the future
	The trace and intersect functions will traverse this first before touching primitives
	I assume I'll remove the primitives vector as primitive pointers will be stored in the acceleration structure instead
	Idk yet though, maybe the structure will store indices for the primitive array instead
	*/
};

void IntersectTraceables(Ray& ray, const std::vector<Traceable*>& traceables, std::vector<Traceable*>& output);