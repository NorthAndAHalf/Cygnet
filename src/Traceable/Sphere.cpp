#include "Sphere.h"
#include "glm/geometric.hpp"

Sphere::Sphere(glm::vec3 _centre, float _radius)
    : centre(_centre), radius(_radius)
{
}

RayHit Sphere::Intersect(const Ray& ray)
{
    glm::vec3 oc = ray.origin - centre;
    float b = glm::dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float h = (b * b) - c;
    if (h < 0.0f) return RayHit();
    h = sqrt(h);
    float t = -b - h;
    if (t <= 0.0f) return RayHit();
    return RayHit(ray, ray.At(t), glm::normalize(ray.At(t) - centre), mat, t);
}

float Sphere::IntersectTest(const Ray& ray)
{
    glm::vec3 oc = ray.origin - centre;
    float b = glm::dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float h = (b * b) - c;
    if (h < 0.0f) return -1.0f;
    h = sqrt(h);
    float t = -b - h;
    if (t <= 0.0f) return -1.0f;
    return t;
}

void Sphere::ApplyMaterial(Material* _mat)
{
    mat = _mat;
}
