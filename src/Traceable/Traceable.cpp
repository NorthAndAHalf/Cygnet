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
    std::vector<RayHit> hits;

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
    return closest;
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

