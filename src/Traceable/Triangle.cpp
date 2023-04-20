#include "Triangle.h"
#include "glm/geometric.hpp"

int Triangle::intersectionCount;

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

	// During test the normal was inverted, I think it's something to do with winding order but for now I'm just inverting it
	// Might just keep this if nothing breaks
	glm::vec3 normal = glm::normalize(- n);
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
	intersectionCount++;
	return t;
}

void Triangle::ApplyMaterial(Material* _mat)
{
	mat = _mat;
}

