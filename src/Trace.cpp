#include "Trace.h"
#include "glm/geometric.hpp"
#include "glm/gtc/random.hpp"
#include "BRDF/BRDF.h"
#include "glm/gtc/constants.hpp"
#include "Scene.h"
#include "BRDF/CookTorrance.h"
#include "glm/mat3x3.hpp"
#include "glm/gtx/rotate_vector.hpp"

glm::vec3 SampleHemisphere(glm::vec3 v, glm::vec3 normal, BRDF* brdf, float& pdf)
{
    // Initially generate a uniform hemispere sample
    glm::vec3 dir = glm::normalize(glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f)));

    // If dir is not inside the hemisphere around the normal, invert it so it is
    if (glm::dot(dir, normal) < 0.0f) dir = -dir;

    glm::vec3 reflect = glm::reflect(v, normal);
    float a2 = brdf->roughness * brdf->roughness;
    a2 *= a2;

    glm::vec3 h = glm::normalize(v + dir);

    glm::vec3 wi = glm::mix(dir, reflect, 1.0f - a2);
    pdf = glm::max(1.0f / (2.0f * glm::pi<float>()) * a2, 0.00001f);
    return wi;
}

/*
glm::vec3 SampleHemisphere(glm::vec3 v, glm::vec3 normal, BRDF* brdf, float& pdf)
{
    // Initially generate a uniform hemispere sample
    glm::vec3 dir = glm::normalize(glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f)));

    // If dir is not inside the hemisphere around the normal, invert it so it is
    if (glm::dot(dir, normal) < 0.0f) dir = -dir;

    pdf = 1.0f / (2.0f * glm::pi<float>());
    return dir;
}
/*
/*glm::vec3 SampleHemisphere(glm::vec3 v, glm::vec3 normal, BRDF* brdf, float& pdf)
{
    float u = glm::linearRand(0.0f, 1.0f);
    float u1 = glm::linearRand(0.0f, 1.0f);
    float a = brdf->roughness * brdf->roughness;
    float a2 = a * a;

    float theta = glm::acos(glm::sqrt((1.0f - u) / u * (a2 - 1.0f) + 1.0f));
    float phi = 2.0f * glm::pi<float>() * u1;

    float x = glm::sin(theta) * glm::cos(phi);
    float y = glm::cos(theta);
    float z = glm::sin(theta) * glm::sin(phi);
    glm::vec3 wm(x, y, z);
    glm::vec3 wi = 2.0f * glm::dot(v, wm) * wm - v;
    float rotTheta = glm::acos(glm::dot(wi, normal));
    glm::vec3 rotAxis = glm::cross(wi, normal);
    wi = glm::rotate(wi, rotTheta, rotAxis);
    pdf = GGXpdf(wi, -v, a2);
    return wi;
}
*/
glm::vec3 TracePath(Ray ray, const Scene& scene, uint8_t bounces, glm::vec3 throughput)
{
    if (bounces >= 4) 
        return glm::vec3(0.0f);

    RayHit hit = scene.Intersect(ray, bounces);

    // Return here if the ray misses
    // Necassary for optimisation but also because material is NULL for ray misses
    if (hit.miss)
        return glm::vec3(0.0f);
    bounces++;

    // Possibly need to multiply this by the BRDF but that can be done in the intersect function and the final result stored at that point's albedo
    glm::vec3 radiance = hit.mat->albedo * hit.mat->emittedIntensity;

    float pdf = 0.0f;
    glm::vec3 dir = SampleHemisphere(ray.direction, hit.normal, hit.mat->brdf, pdf);

    glm::vec3 brdf = hit.mat->brdf->Calculate(ray.direction, hit.normal, -dir, hit.mat->albedo);
    throughput *= brdf * glm::dot(hit.normal, dir) / pdf;
    ray = Ray(hit.pos, dir);
    radiance += throughput * TracePath(ray, scene, bounces, throughput);

    return radiance;
}

glm::vec3 DebugTrace(Ray ray, const Scene& scene)
{
    RayHit hit = scene.Intersect(ray, 0);
    if (hit.miss) return glm::vec3(0.0f);
    glm::vec3 n = hit.normal;
    return hit.mat->albedo;
}

