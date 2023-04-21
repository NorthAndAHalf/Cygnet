#include "BVH.h"
#include "DebugCounter.h"

void SAHSplit(std::vector<Triangle*>* primitives, std::vector<Triangle*>* v1, std::vector<Triangle*>* v2)
{	
	// X axis
	std::sort(primitives->begin(), primitives->end(), [](Triangle* t1, Triangle* t2) -> bool
		{
			return t1->GetCentroid().x < t2->GetCentroid().x;
		});

	float xCost = -1.0f;
	unsigned int xIndex;

	for (int i = 0; i < primitives->size(); i++)
	{
		float leftArea = 0;
		float rightArea = 0;

		for (int j = 0; j < i; j++)
		{
			leftArea += primitives->at(j)->GetArea();
		}
		for (int j = i + 1; j < primitives->size(); j++)
		{
			rightArea += primitives->at(j)->GetArea();
		}

		float cost = leftArea * i + rightArea * (primitives->size() - i);

		if (xCost == -1.0f || cost < xCost)
		{
			xCost = cost;
			xIndex = i;
		}
	}

	// Y axis
	std::sort(primitives->begin(), primitives->end(), [](Triangle* t1, Triangle *t2) -> bool
		{
			return t1->GetCentroid().y < t2->GetCentroid().y;
		});

	float yCost = -1.0f;
	unsigned int yIndex;

	for (int i = 0; i < primitives->size(); i++)
	{
		float leftArea = 0;
		float rightArea = 0;

		for (int j = 0; j < i; j++)
		{
			leftArea += primitives->at(j)->GetArea();
		}
		for (int j = i + 1; j < primitives->size(); j++)
		{
			rightArea += primitives->at(j)->GetArea();
		}

		float cost = leftArea * i + rightArea * (primitives->size() - i);

		if (yCost == -1.0f || cost < yCost)
		{
			yCost = cost;
			yIndex = i;
		}
	}

	// Z axis
	std::sort(primitives->begin(), primitives->end(), [](Triangle* t1, Triangle* t2) -> bool
		{
			return t1->GetCentroid().z < t2->GetCentroid().z;
		});

	float zCost = -1.0f;
	unsigned int zIndex;

	for (int i = 0; i < primitives->size(); i++)
	{
		float leftArea = 0;
		float rightArea = 0;

		for (int j = 0; j < i; j++)
		{
			leftArea += primitives->at(j)->GetArea();
		}
		for (int j = i + 1; j < primitives->size(); j++)
		{
			rightArea += primitives->at(j)->GetArea();
		}

		float cost = leftArea * i + rightArea * (primitives->size() - i);

		if (zCost == -1.0f || cost < zCost)
		{
			zCost = cost;
			zIndex = i;
		}
	}

	// Lowest Cost
	unsigned int bestIndex;

	if (xCost < yCost && xCost < zCost)
	{
		bestIndex = xIndex;
		std::sort(primitives->begin(), primitives->end(), [](Triangle* t1, Triangle* t2) -> bool
			{
				return t1->GetCentroid().x < t2->GetCentroid().x;
			});
	}
	else if (yCost < xCost && yCost < zCost)
	{
		bestIndex = yIndex;
		std::sort(primitives->begin(), primitives->end(), [](Triangle* t1, Triangle* t2) -> bool
			{
				return t1->GetCentroid().y < t2->GetCentroid().y;
			});
	}
	else
	{
		bestIndex = zIndex;
		std::sort(primitives->begin(), primitives->end(), [](Triangle* t1, Triangle* t2) -> bool
			{
				return t1->GetCentroid().z < t2->GetCentroid().z;
			});
	}

	for (int i = 0; i < primitives->size(); i++)
	{
		if (i < bestIndex)
		{
			v1->push_back(primitives->at(i));
		}
		else
		{
			v2->push_back(primitives->at(i));
		}
	}
}

std::shared_ptr<AABB> ConstructAABB(std::vector<Triangle*>* primitives, unsigned int maxTriangles)
{
	if (primitives->size() > maxTriangles)
	{
		std::vector<Triangle*> v1;
		std::vector<Triangle*> v2;

		SAHSplit(primitives, &v1, &v2);

		std::shared_ptr<AABB> bb1 = ConstructAABB(&v1, maxTriangles);
		std::shared_ptr<AABB> bb2 = ConstructAABB(&v2, maxTriangles);

		return std::make_shared<AABB>(bb1, bb2);
	}
	else
	{
		return std::make_shared<AABB>(primitives);
	}
}

BVH::BVH(std::vector<Triangle*>* primitives, unsigned int maxTriangles)
{
	root = ConstructAABB(primitives, maxTriangles);
}

bool BVH::Intersect(const Ray& ray, std::vector<RayHit>* hits)
{
	return root->Intersect(ray, hits);
}
