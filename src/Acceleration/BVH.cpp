#include "BVH.h"

std::shared_ptr<AABB> ConstructAABB(std::vector<Primitive*>* primitives, unsigned int maxTriangles)
{
	if (primitives->size() > maxTriangles)
	{
		// SAH split here

		std::vector<Primitive*> v1 (primitives->begin(), primitives->begin() + primitives->size() / 2);
		std::vector<Primitive*> v2 (primitives->begin() + primitives->size() / 2, primitives->end());

		std::shared_ptr<AABB> bb1 = ConstructAABB(&v1, maxTriangles);
		std::shared_ptr<AABB> bb2 = ConstructAABB(&v2, maxTriangles);

		return std::make_shared<AABB>(bb1, bb2);
	}
	else
	{
		return std::make_shared<AABB>(primitives);
	}
}

BVH::BVH(std::vector<Primitive*>* primitives, unsigned int maxTriangles)
{
	root = ConstructAABB(primitives, maxTriangles);
}

bool BVH::Intersect(const Ray& ray, std::vector<RayHit>* hits)
{
	return root->Intersect(ray, hits);
}