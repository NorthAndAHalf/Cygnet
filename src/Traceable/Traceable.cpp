#include "Traceable.h"

Traceable::Traceable()
    : primitives(new std::vector<Primitive*>)
{
}

Traceable::~Traceable()
{
    delete primitives;
}

RayHit Traceable::Trace(Ray& ray, uint8_t depth)
{
    // The acceleration structure for each traceable will be traced in this function
    std::vector<RayHit> hits;
    for (Primitive* p : *primitives)
    {
        RayHit h = p->Trace(ray, depth);
        hits.push_back(h); 
    }

    RayHit output;
    for (RayHit h : hits)
    {
        if ((h.t < output.t && h.depth != -1) || output.depth == -1) output = h; // Hits with negative depth are misses (no intersection)
    }

    return output;
}

float Traceable::Intersect(Ray& ray)
{
    // TODO: Return t value of closest intersection
    for (Primitive* p : *primitives)
    {
        p->Trace(ray, 0);
    }
    return -1.0f;
}

float Traceable::Intersect(Ray& ray, glm::vec3& colour)
{
    // TODO: Return t value of closest intersection and output the colour of the intersection colour at the intersecion point
    for (Primitive* p : *primitives)
    {
        p->Trace(ray, 0);
    }

    colour = glm::vec3(0.0f);
    return -1.0f;
}

void Traceable::AddPrimitive(Primitive* p)
{
    primitives->push_back(p);
}
