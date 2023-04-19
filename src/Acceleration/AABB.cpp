#include "AABB.h"
#include "glm/vec3.hpp"
#include "glm/common.hpp"
#include <optional>
#include "Traceable/Triangle.h"

AABB::AABB(std::vector<Primitive*>* primitives)
{
	isLeaf = true;
	left = nullptr;
	right = nullptr;

	std::optional<float> minX;
	std::optional<float> maxX;
	std::optional<float> minY;
	std::optional<float> maxY;
	std::optional<float> minZ;
	std::optional<float> maxZ;

	for (Primitive* p : *primitives)
	{
		Triangle* t = (Triangle*)p;
		triangles.push_back(t);

		// X
		if (!minX.has_value())
		{
			minX.emplace(t->P1.x);
		}

		if (t->P1.x < minX.value()) minX.emplace(t->P1.x);
		if (t->P2.x < minX.value()) minX.emplace(t->P2.x);
		if (t->P3.x < minX.value()) minX.emplace(t->P3.x);

		if (!maxX.has_value())
		{
			maxX.emplace(t->P1.x);
		}

		if (t->P1.x > maxX.value()) maxX.emplace(t->P1.x);
		if (t->P2.x > maxX.value()) maxX.emplace(t->P2.x);
		if (t->P3.x > maxX.value()) maxX.emplace(t->P3.x);

		// Y
		if (!minY.has_value())
		{
			minY.emplace(t->P1.y);
		}

		if (t->P1.y < minY.value()) minY.emplace(t->P1.y);
		if (t->P2.y < minY.value()) minY.emplace(t->P2.y);
		if (t->P3.y < minY.value()) minY.emplace(t->P3.y);

		if (!maxY.has_value())
		{
			maxY.emplace(t->P1.y);
		}

		if (t->P1.y > maxY.value()) maxY.emplace(t->P1.y);
		if (t->P2.y > maxY.value()) maxY.emplace(t->P2.y);
		if (t->P3.y > maxY.value()) maxY.emplace(t->P3.y);

		// Z
		if (!minZ.has_value())
		{
			minZ.emplace(t->P1.z);
		}

		if (t->P1.z < minZ.value()) minZ.emplace(t->P1.z);
		if (t->P2.z < minZ.value()) minZ.emplace(t->P2.z);
		if (t->P3.z < minZ.value()) minZ.emplace(t->P3.z);

		if (!maxZ.has_value())
		{
			maxZ.emplace(t->P1.z);
		}

		if (t->P1.z > maxZ.value()) maxZ.emplace(t->P1.z);
		if (t->P2.z > maxZ.value()) maxZ.emplace(t->P2.z);
		if (t->P3.z > maxZ.value()) maxZ.emplace(t->P3.z);	
	}
	min = glm::vec3(minX.value(), minY.value(), minZ.value());
	max = glm::vec3(maxX.value(), maxY.value(), maxZ.value());
}

AABB::AABB(std::shared_ptr<AABB> _left, std::shared_ptr<AABB> _right)
{
	left = _left;
	right = _right;
	isLeaf = false;
	min = glm::min(left->min, right->min);
	max = glm::max(left->max, right->max);
}

bool AABB::Intersect(const Ray& ray, std::vector<RayHit>* hits)
{
	glm::vec3 tMin = (min - ray.origin) / ray.direction;
	glm::vec3 tMax = (max - ray.origin) / ray.direction;
	glm::vec3 t1 = glm::min(tMin, tMax);
	glm::vec3 t2 = glm::max(tMin, tMax);
	float tNear = glm::max(glm::max(t1.x, t1.y), t1.z);
	float tFar = glm::min(glm::min(t2.x, t2.y), t2.z);
	bool intersected = tNear < tFar;

	if (intersected)
	{
		if (isLeaf)
		{
			for (Triangle* t : triangles)
			{
				intersected = false;
				if (t->IntersectTest(ray))
				{
					intersected = true;
					hits->push_back(t->Intersect(ray));
				}
			}
		}
		else
		{
			intersected = left->Intersect(ray, hits) || right->Intersect(ray, hits);
		}
	}

	return intersected;
}

std::vector<Triangle*>& AABB::GetTriangles()
{
	return triangles;
}
