#include "Trace.h"
#include "glm/geometric.hpp"
#include "glm/gtc/random.hpp"
#include "BRDF/BRDF.h"
#include "glm/gtc/constants.hpp"
#include "Scene.h"

glm::vec3 Trace(const RayHit& hitPoint, const std::vector<Traceable*>& traceables, uint8_t depth, uint8_t limit)
{
    if (depth > limit) return glm::vec3(0.0f);
    depth++;
    // Return default colour if no traceables are hit by the ray, just black for now but could sample an environment map in the future
    if (hitPoint.t == -1.0f)
        return glm::vec3(0.0f);

    int samples = 16;

    glm::vec3 integration = glm::vec3(0.0f);

    // Need to add russian roulette, atm just using a hard recursion limit for stopping criteria

    // Light transport integral
    for (int i = 0; i < samples; i++)
    {
        glm::vec3 dir = glm::normalize(glm::vec3(glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f)));

        // If dir is not inside the hemisphere around the normal, invert it so it is
        if (glm::dot(dir, hitPoint.normal) < 0.0f) dir = -dir;
        Ray newRay = Ray(hitPoint.pos, dir);
        RayHit closest = IntersectTraceables(newRay, traceables);
        glm::vec3 Li = Trace(closest, traceables, depth, limit);

        // PDF is hardcoded atm, might have to change this once I implement importance sampling
        // Linear PDF
        constexpr float pdf = 1.0f / (2.0f * glm::pi<float>());

        integration += Li * hitPoint.BRDFCalculate() * glm::dot(dir, hitPoint.normal) * pdf;
    }

    // Rendering Equation:
    integration /= (float)samples;

    glm::vec3 Le = hitPoint.mat.albedo * hitPoint.mat.emittedIntensity;
    return Le + integration;
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

glm::vec3 PathTrace(const Ray& ray, const Scene& scene)
{
    return glm::vec3(0.0f);
}
