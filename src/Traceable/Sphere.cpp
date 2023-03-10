#include "Sphere.h"
#include "glm/geometric.hpp"

Sphere::Sphere(glm::vec3 _centre, float _radius)
    : centre(_centre), radius(_radius)
{
}

glm::vec3 Sphere::Trace(Ray& ray)
{
    return glm::vec3();
}

float Sphere::Intersect(Ray& ray)
{
    glm::vec3 oc = ray.origin - centre;
    double b = glm::dot(oc, ray.direction);
    double c = dot(oc, oc) - radius * radius;
    double h = b * b - c;
    if (h < 0.0) return -1.0f;
    h = sqrt(h);
    double t = -b - h;
    return t;
}

float Sphere::Intersect(Ray& ray, glm::vec3& colour)
{
    float t = Intersect(ray);
    // Sample colour from texture or something from ray.At(t) idk, just a hardcoded colour for now
    colour = glm::vec3(1.0f, 0.0f, 0.0f);
    return t;
}
