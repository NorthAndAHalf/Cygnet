#pragma once
#include "pch.h"
#include <vector>
#include "Primitive.h"
#include "glm/vec3.hpp"
#include "Ray.h"
#include "Models/Model.h"
#include "Acceleration/BVH.h"

class Traceable
{
public:
	Traceable();
	~Traceable();

	RayHit Intersect(const Ray& ray);

	void AddPrimitive(Primitive* p);
	void AddModel(const Model& model);

	void ConstructBVH();
	void ApplyMaterial(Material* mat);
	unsigned int NumberOfPrimitives();

	bool ignoreFirst = false;
	bool hasBVH;

private:
	std::vector<Primitive*>* primitives; 

	std::unique_ptr<BVH> bvh;

	/*
	Will require an acceleration structure to be stored here in the future
	The trace and intersect functions will traverse this first before touching primitives
	I assume I'll remove the primitives vector as primitive pointers will be stored in the acceleration structure instead
	Idk yet though, maybe the structure will store indices for the primitive array instead
	*/
};

