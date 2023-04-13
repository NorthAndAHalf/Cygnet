#include "Scene.h"

RayHit IntersectTraceablesIgnoreFirst(const Ray& ray, const std::vector<Traceable*>& traceables)
{
    // Traverse the BVH of each traceable to find primitive intersections if there are any
    // Once BVHs are implemented
    std::vector<RayHit> hits;

    for (Traceable* t : traceables)
    {
        if (t->ignoreFirst)
            continue;
        hits.push_back(t->Intersect(ray));
    }


    RayHit closest = RayHit();
    for (const RayHit& h : hits)
    {
        if (h.t == -1.0f)
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

RayHit IntersectTraceables(const Ray& ray, const std::vector<Traceable*>& traceables)
{
    // Traverse the BVH of each traceable to find primitive intersections if there are any
    // Once BVHs are implemented
    std::vector<RayHit> hits;

    for (Traceable* t : traceables)
        hits.push_back(t->Intersect(ray));

    RayHit closest = RayHit();
    for (const RayHit& h : hits)
    {
        if (h.t == -1.0f)
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

Scene::Scene(std::vector<Traceable*>* _traceables)
	: traceables(_traceables)
{}

void Scene::SetTraceables(std::vector<Traceable*>*_traceables)
{
	traceables = _traceables;
}

const std::vector<Traceable*>* Scene::GetTraceables() const
{
	return traceables;
}

RayHit Scene::Intersect(const Ray& ray, uint8_t bounces) const
{
    if (bounces < 1) return IntersectTraceablesIgnoreFirst(ray, *traceables);
    
    return IntersectTraceables(ray, *traceables);
}
