#include "Triangle.h"
#include "glm/geometric.hpp"

// Triangle intersection test adapted from Inigo Quilez's shadertoy under the MIT license https://www.shadertoy.com/view/MlGcDz

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	: P1(p1), P2(p2), P3(p3)
{
}

RayHit Triangle::Intersect(const Ray& ray)
{
	glm::vec3 p2p1 = P2 - P1;
	glm::vec3 p3p1 = P3 - P1;
	glm::vec3 rop1 = ray.origin - P1;

	glm::vec3 n = glm::cross(p2p1, p3p1);
	glm::vec3 q = cross(rop1, ray.direction);
	float d = 1.0f / glm::dot(ray.direction, n);
	float u = d * glm::dot(-q, p3p1);
	float v = d * glm::dot(q, p2p1);
	float t = d * glm::dot(-n, rop1);

	glm::vec3 normal = glm::normalize(n);
	if (u < 0.0f || v < 0.0f || (u + v) > 1.0f || t <= 0.0f) t = -1.0f;
	if (t <= 0.0f) return RayHit();
	return RayHit(ray, ray.At(t), normal, mat, t);
}

float Triangle::IntersectTest(const Ray& ray)
{
	glm::vec3 p2p1 = P2 - P1;
	glm::vec3 p3p1 = P3 - P1;
	glm::vec3 rop1 = ray.origin - P1;

	glm::vec3 n = glm::cross(p2p1, p3p1);
	glm::vec3 q = cross(rop1, ray.direction);
	float d = 1.0f / glm::dot(ray.direction, n);
	float u = d * glm::dot(-q, p3p1);
	float v = d * glm::dot(q, p2p1);
	float t = d * glm::dot(-n, rop1);

	if (u < 0.0f || v < 0.0f || (u + v) > 1.0f || t <= 0.0f) t = -1.0f;
	return t;
}

void Triangle::ApplyMaterial(Material* _mat)
{
	mat = _mat;
}

glm::vec3 Triangle::GetCentroid()
{
	float x = (P1.x + P2.x + P3.x) / 3;
	float y = (P1.y + P2.y + P3.y) / 3;
	float z = (P1.z + P2.z + P3.z) / 3;

	return glm::vec3(x, y, z);
}

float Triangle::GetArea()
{
	glm::vec3 p2p1 = P2 - P1;
	glm::vec3 p3p1 = P3 - P1;

	float h = glm::length(glm::cross(p2p1, p3p1)) / p2p1.length();
	float b = p3p1.length() * h / p2p1.length();

	return 0.5f * b * h;
}
