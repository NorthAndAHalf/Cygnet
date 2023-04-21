#include "AABB.h"
#include "glm/vec3.hpp"
#include "glm/common.hpp"
#include "Traceable/Triangle.h"

AABB::AABB(std::vector<Triangle*>* primitives)
{
	isLeaf = true;
	left = nullptr;
	right = nullptr;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	bool hasMinX = false;
	bool hasMaxX = false;
	bool hasMinY = false;
	bool hasMaxY = false;
	bool hasMinZ = false;
	bool hasMaxZ = false;

	for (Triangle* t : *primitives)
	{
		triangles.push_back(t);

		// X
		if (!hasMinX)
		{
			minX = t->P1.x;
			hasMinX = true;
		}

		if (t->P1.x < minX) minX = t->P1.x;
		if (t->P2.x < minX) minX = t->P2.x;
		if (t->P3.x < minX) minX = t->P3.x;

		if (!hasMaxX)
		{
			maxX = t->P1.x;
			hasMaxX = true;
		}

		if (t->P1.x > maxX) maxX = t->P1.x;
		if (t->P2.x > maxX) maxX = t->P2.x;
		if (t->P3.x > maxX) maxX = t->P3.x;

		// Y
		if (!hasMinY)
		{
			minY = t->P1.y;
			hasMinY = true;
		}

		if (t->P1.y < minY) minY = t->P1.y;
		if (t->P2.y < minY) minY = t->P2.y;
		if (t->P3.y < minY) minY = t->P3.y;

		if (!hasMaxY)
		{
			maxY = t->P1.y;
			hasMaxY = true;
		}

		if (t->P1.y > maxY) maxY = t->P1.y;
		if (t->P2.y > maxY) maxY = t->P2.y;
		if (t->P3.y > maxY) maxY = t->P3.y;

		// Z
		if (!hasMinZ)
		{
			minZ = t->P1.z;
			hasMinZ = true;
		}

		if (t->P1.z < minZ) minZ = t->P1.z;
		if (t->P2.z < minZ) minZ = t->P2.z;
		if (t->P3.z < minZ) minZ = t->P3.z;

		if (!hasMaxZ)
		{
			maxZ = t->P1.z;
			hasMaxZ = true;
		}

		if (t->P1.z > maxZ) maxZ = t->P1.z;
		if (t->P2.z > maxZ) maxZ = t->P2.z;
		if (t->P3.z > maxZ) maxZ = t->P3.z;	
	}
	min = glm::vec3(minX, minY, minZ);
	max = glm::vec3(maxX, maxY, maxZ);
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
			intersected = false;
			for (Triangle* t : triangles)
			{
				if (t->IntersectTest(ray) != -1.0f)
				{
					intersected = true;
					hits->push_back(t->Intersect(ray));
				}
			}
		}
		else
		{
			bool leftHit = left->Intersect(ray, hits);
			bool rightHit = right->Intersect(ray, hits);
			intersected = leftHit || rightHit;
		}
	}

	return intersected;
}

std::vector<Triangle*>& AABB::GetTriangles()
{
	return triangles;
}

float AABB::GetArea()
{
	float area = 0;

	for (Triangle* t : triangles)
	{
		area += t->GetArea();
	}
	return area;
}
