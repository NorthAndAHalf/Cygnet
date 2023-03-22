#include "AABB.h"
#include "glm/vec3.hpp"
#include "glm/common.hpp"

AABB::AABB(float _minX, float _maxX, float _minY, float _maxY, float _minZ, float _maxZ)
    : minX(_minX), maxX(_maxX), minY(_minY), maxY(_maxY), minZ(_minZ), maxZ(_maxZ)
{
}

float AABB::Intersect(const Ray& ray)
{
    glm::vec3 m = 1.0f / ray.direction;
    glm::vec3 n = m * ray.origin;
    glm::vec3 size = glm::vec3(glm::abs(maxX - minX), glm::abs(maxY - minY), glm::abs(maxZ - minZ));
    glm::vec3 k = glm::abs(m) * size;


    return -1.0f;
}
