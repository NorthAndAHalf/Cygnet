#include "AABB.h"
#include "glm/vec3.hpp"
#include "glm/common.hpp"

AABB::AABB(float _minX, float _maxX, float _minY, float _maxY, float _minZ, float _maxZ)
    : minX(_minX), maxX(_maxX), minY(_minY), maxY(_maxY), minZ(_minZ), maxZ(_maxZ)
{
}

bool AABB::Intersect(const Ray& ray)
{
    float tmin_x = (minX - ray.origin.x) * -ray.direction.x;
    float tmax_x = (maxX - ray.origin.x) * -ray.direction.x;
    float tmin_y = (minY - ray.origin.y) * -ray.direction.y;
    float tmax_y = (maxY - ray.origin.y) * -ray.direction.y;
    float tmin_z = (minZ - ray.origin.z) * -ray.direction.z;
    float tmax_z = (maxZ - ray.origin.z) * -ray.direction.z;

    float tmin = glm::max(glm::max(tmin_x, tmin_y), tmin_z);
    float tmax = glm::min(glm::min(tmax_x, tmax_y), tmax_z);

    return tmax > tmin;
}
