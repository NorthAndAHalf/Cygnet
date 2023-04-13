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

	RayHit Intersect(const Ray& ray);

	void AddPrimitive(Primitive* p);
	void ApplyMaterial(std::shared_ptr<Material> mat);

	bool ignoreFirst = false;

private:
	std::vector<Primitive*>* primitives; 

	/*
	Will require an acceleration structure to be stored here in the future
	The trace and intersect functions will traverse this first before touching primitives
	I assume I'll remove the primitives vector as primitive pointers will be stored in the acceleration structure instead
	Idk yet though, maybe the structure will store indices for the primitive array instead
	*/
};

