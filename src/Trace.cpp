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
    /*
    // Inversion method importance sampling of the GGX NDF
    float roughness = brdf->roughness * brdf->roughness;
    roughness *= roughness;

    float u1 = glm::linearRand(0.0f, 1.0f);
    float u2 = glm::linearRand(0.0f, 1.0f);
    // old
    float theta = glm::atan(glm::sqrt(-roughness * glm::log(1 - u1)));
    float phi = 2 * glm::pi<float>() * u2;

    float x = glm::sin(theta) * glm::cos(phi);
    float y = glm::sin(theta) * glm::sin(phi);
    float z = glm::cos(theta);

    glm::vec3 T = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), normal));
    glm::mat3x3 tangentSpaceTransform(T, normal, glm::cross(T, normal));

    glm::vec3 dir = glm::normalize(tangentSpaceTransform * glm::vec3(x, y, z));
    glm::vec3 H = glm::normalize(v + dir);
    float D = Dist(normal, H, brdf->roughness); // Dist performs the squares on the roughness, do not pass in the squared values

    float ndoth = glm::max(glm::dot(normal, H), 0.00001f);
    float vdoth = glm::max(glm::dot(v, H), 0.00001f);
    float pdfH = 1.0f / (2.0f * glm::pi<float>() * (1.0f - ndoth * ndoth) * glm::sqrt(roughness));

    pdf = D * ndoth / (4.0f * vdoth * pdfH);
    return dir;

    // new
    float theta = glm::acos(glm::sqrt((1.0f - u1) / u1 * (roughness - 1.0f) + 1.0f));
    float phi = 2.0f * glm::pi<float>() * u2;
    
    float x = glm::sin(theta) * glm::cos(phi);
    float y = glm::cos(theta);
    float z = glm::sin(theta) * glm::sin(phi);

    glm::vec3 wm(x, y, z);
    glm::vec3 wi = 2.0f * glm::dot(-v, wm) * wm - -v;

    float rotTheta = glm::acos(glm::dot(wi, normal));
    glm::vec3 rotAxis = glm::cross(wi, normal);
    wi = glm::rotate(wi, rotTheta, rotAxis);
    pdf = (Dist(normal, wm, roughness) * glm::dot(wm, glm::vec3(0.0f, 1.0f, 0.0f))) / 4.0f * glm::dot(-v, wm);
    return wi;
    */
    // Initially generate a uniform hemispere sample
    glm::vec3 dir = glm::normalize(glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f)));

    // If dir is not inside the hemisphere around the normal, invert it so it is
    if (glm::dot(dir, normal) < 0.0f) dir = -dir;


    p = glm::max(glm::dot(dir, normal) / glm::pi<float>(), 0.001f);

    return dir;
}

glm::vec3 TracePath(Ray ray, const Scene& scene, uint8_t bounces)
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
    ray = Ray(hit.pos, dir);
    radiance += brdf * TracePath(ray, scene, bounces) * glm::dot(hit.normal, ray.direction) / pdf;

    return radiance;
}

glm::vec3 DebugTrace(Ray ray, const Scene& scene)
{
    RayHit hit = scene.Intersect(ray, 0);
    if (hit.miss) return glm::vec3(0.0f);
    glm::vec3 n = hit.normal;
    return hit.mat->albedo;
}

