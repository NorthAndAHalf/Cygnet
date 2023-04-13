#include "Trace.h"
#include "glm/geometric.hpp"
#include "glm/gtc/random.hpp"
#include "BRDF/BRDF.h"
#include "glm/gtc/constants.hpp"
#include "Scene.h"

glm::vec3 SampleHemisphere(glm::vec3 normal, float& p)
{
    // Uniform distribution currently, no importance sampling

    // Uniformly sample the unit sphere
    glm::vec3 dir = glm::normalize(glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f)));

    // If dir is not inside the hemisphere around the normal, invert it so it is
    if (glm::dot(dir, normal) < 0.0f) dir = -dir;
    p = glm::dot(dir, normal) / glm::pi<float>();
    return dir;
}

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
        // IntersectTraceables is implemented in Scene.cpp, don't ask
        RayHit closest = IntersectTraceables(newRay, traceables);
        glm::vec3 Li = Trace(closest, traceables, depth, limit);

        // PDF is hardcoded atm, might have to change this once I implement importance sampling
        // Linear PDF
        constexpr float pdf = 1.0f / (2.0f * glm::pi<float>());

        integration += Li * hitPoint.mat->brdf->Calculate(hitPoint.ray.direction, hitPoint.normal, dir, hitPoint.mat->albedo) * glm::dot(dir, hitPoint.normal) / pdf;
    }

    // Rendering Equation:
    integration /= (float)samples;

    glm::vec3 Le = hitPoint.mat->albedo * hitPoint.mat->emittedIntensity;
    return Le + integration;
}

glm::vec3 TracePath(Ray ray, const Scene& scene, uint8_t bounces)
{
    if (bounces >= 3) return glm::vec3(0.0f);

    RayHit hit = scene.Intersect(ray, bounces);
    bounces++;

    // Possibly need to multiply this by the BRDF but that can be done in the intersect function and the final result stored at that point's albedo
    glm::vec3 radiance = hit.mat->albedo * hit.mat->emittedIntensity;
    if (hit.mat->emittedIntensity > 0.0f) return radiance; // Do not integrate over emissive surfaces, just return the emitted light


    float p = 0.0f;
    glm::vec3 dir = SampleHemisphere(hit.normal, p);

    ray = Ray(hit.pos, dir);
    glm::vec3 brdf = hit.mat->brdf->Calculate(-ray.direction, hit.normal, -dir, hit.mat->albedo);
    radiance += brdf * TracePath(ray, scene, bounces) * glm::dot(hit.normal, ray.direction) / p;

    return radiance;
}
// Remember to show examples of Trace() vs TracePath() in diss
// Talk about timings too
