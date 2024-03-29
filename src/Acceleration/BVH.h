#pragma once

#include "AABB.h"
#include "Traceable/Triangle.h"
#include <vector>


class BVH
{
public:
	BVH(std::vector<Triangle*>* primitives, unsigned int maxTriangles);

	bool Intersect(const Ray& ray, std::vector<RayHit>* hits);
private:
	std::shared_ptr<AABB> root;
};