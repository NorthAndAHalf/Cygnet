#include "Trace.h"
#include "glm/geometric.hpp"
#include "glm/gtc/random.hpp"
#include "BRDF/BRDF.h"
#include "glm/gtc/constants.hpp"
#include "Scene.h"

glm::vec3 SampleHemisphere(glm::vec3 normal, float& p)
{
    // Initially generate a uniform hemispere sample
    glm::vec3 dir = glm::normalize(glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f)));

    // If dir is not inside the hemisphere around the normal, invert it so it is
    if (glm::dot(dir, normal) < 0.0f) dir = -dir;


    p = glm::max(glm::dot(dir, normal) / glm::pi<float>(), 0.001f);

    return dir;
}

glm::vec3 TracePath(Ray ray, const Scene& scene, uint8_t bounces)
{
    if (bounces >= 3) 
        return glm::vec3(0.0f);

    RayHit hit = scene.Intersect(ray, bounces);

    // Return here if the ray misses
    // Necassary for optimisation but also because material is NULL for ray misses
    if (hit.miss)
        return glm::vec3(0.0f);
    bounces++;

    // Possibly need to multiply this by the BRDF but that can be done in the intersect function and the final result stored at that point's albedo
    glm::vec3 radiance = hit.mat->albedo * hit.mat->emittedIntensity;

    float p = 0.0f;
    glm::vec3 dir = SampleHemisphere(hit.normal, p);

    ray = Ray(hit.pos, dir);
    glm::vec3 brdf = hit.mat->brdf->Calculate(ray.direction, hit.normal, -dir, hit.mat->albedo);
    radiance += brdf * TracePath(ray, scene, bounces) * glm::dot(hit.normal, ray.direction) / p;

    return radiance;
}

glm::vec3 DebugTrace(Ray ray, const Scene& scene)
{
    RayHit hit = scene.Intersect(ray, 0);
    if (hit.miss) return glm::vec3(0.0f);
    glm::vec3 n = hit.normal;
    return hit.mat->albedo;
}

