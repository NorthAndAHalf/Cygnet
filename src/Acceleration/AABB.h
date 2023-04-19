#pragma once
#include "Ray.h"
#include <vector>
#include "Traceable/Triangle.h"
#include <memory>

struct AABB
{
	AABB(std::vector<Primitive*>* primitives);
	AABB(std::shared_ptr<AABB> _left, std::shared_ptr<AABB> right);

	bool Intersect(const Ray& ray, std::vector<RayHit>* hits);

	// Triangles are stored as indices for the primitives vector stored in each traceable
	std::vector<Triangle*>& GetTriangles();

	glm::vec3 min;
	glm::vec3 max;
	bool isLeaf;
	std::shared_ptr<AABB> left;
	std::shared_ptr<AABB> right;

private:
	std::vector<Triangle*> triangles;
};
