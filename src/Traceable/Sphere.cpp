#include "Sphere.h"
#include "glm/geometric.hpp"

Sphere::Sphere(glm::vec3 _centre, float _radius)
    : centre(_centre), radius(_radius)
{
}

RayHit Sphere::Trace(Ray& ray, uint8_t depth)
{
    glm::vec3 surfaceContribution;
    glm::vec3 normal;
    float t = Intersect(ray, surfaceContribution, normal);

    if (t < 0.0f) return RayHit(glm::vec3(0.0f), ray.direction, glm::vec3(0.0f), glm::vec3(0.0f), 0.0f, 0.0f, -1);

    glm::vec3 reflectedContribution = glm::vec3(0.8f); // Temporary, just so I can get a sphere rendering atm

    glm::vec3 colour = (surfaceContribution * reflectedContribution);
    RayHit output = RayHit(ray.At(t), ray.direction, normal, colour, 0.0f, t, depth);
    return output;
}

float Sphere::Intersect(Ray& ray, glm::vec3& normal)
{
    glm::vec3 oc = ray.origin - centre; 
    float b = glm::dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float h = (b * b) - c; //spdlog::trace(c);
    if (h < 0.0f) return -1.0f;
    h = sqrt(h);
    float t = -b - h;
    return t;
}

float Sphere::Intersect(Ray& ray, glm::vec3& colour, glm::vec3& normal)
{
    float t = Intersect(ray, normal);
    // Sample colour from texture or something from ray.At(t) idk, just a hardcoded colour for now
    colour = glm::vec3(1.0f, 0.0f, 0.0f);
    return t;
}
