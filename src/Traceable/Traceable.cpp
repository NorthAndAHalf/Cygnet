#include "Traceable.h"
#include "RayHit.h"
#include "glm/gtc/random.hpp"

Traceable::Traceable()
    : primitives(new std::vector<Primitive*>)
{
}

Traceable::~Traceable()
{
    delete primitives;
}

RayHit Traceable::Intersect(const Ray& ray)
{
    // Might need to replace this code once BVH is implemented
    std::pair<Primitive*, float> closest = std::pair<Primitive*, float>(nullptr, -1.0f);
    bool miss = true;

    for (Primitive* p : *primitives)
    {
        float t = p->IntersectTest(ray);

        if (t == -1.0f)
        {
            continue;
        }

        if (closest.first == nullptr)
        {
            closest.first = p;
            closest.second = t;
            miss = t == -1.0f;
            continue;
        }

        if (closest.second > t && t > 0.0001f)
        {
            closest.first = p;
            closest.second = t;
        }
    }

    if (miss)
    {
        return RayHit();
    }

    return closest.first->Intersect(ray);


    /*std::vector<RayHit> hits;

    for (Primitive* p : *primitives)
        hits.push_back(p->Intersect(ray));

    if (hits.empty()) return RayHit();

    RayHit closest = RayHit();
    for (RayHit h : hits)
    {
        if (h.t < 0.0001f)
            continue;
        
        if (closest.t == -1.0f)
        {
            closest = h;
            continue;
        }

        if (h.t < closest.t)
        {
            closest = h;
        }
    }
    return closest;*/
}

void Traceable::AddPrimitive(Primitive* p)
{
    primitives->push_back(p);
}

void Traceable::ApplyMaterial(Material* mat)
{
    for (Primitive* p: *primitives)
    {
        p->ApplyMaterial(mat);
    }
}

