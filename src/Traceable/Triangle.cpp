#include "Triangle.h"
#include "glm/geometric.hpp"

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	: P1(p1), P2(p2), P3(p3)
{
}

RayHit Triangle::Trace(Ray& ray, uint8_t depth)
{
	glm::vec3 surfaceContribution;
	glm::vec3 normal;
	float t = Intersect(ray, surfaceContribution, normal);

	if (t < 0.0f) return RayHit(glm::vec3(0.0f), ray.direction, glm::vec3(0.0f), glm::vec3(0.0f), 0.0f, 0.0f, -1);

	glm::vec3 reflectedContribution = glm::vec3(0.8f);

	glm::vec3 colour = (surfaceContribution * reflectedContribution);
	RayHit output = RayHit(ray.At(t), ray.direction, normal, colour, 0.0f, t, depth);
}

float Triangle::Intersect(Ray& ray, glm::vec3& normal)
{
	glm::vec3 p2p1 = P2 - P1;
	glm::vec3 p3p1 = P3 - P1;
	glm::vec3 rop1 = ray.origin - P1;

	glm::vec3 n = glm::cross(p2p1, p3p1);
	glm::vec3 q = cross(rop1, ray.direction);
	float d = 1.0f / glm::dot(ray.direction, n);
	float u = d * glm::dot(-q, p3p1);
	float v = d * glm::dot( q, p2p1);
	float t = d * glm::dot(-n, rop1);
	if (u < 0.0f || v < 0.0f || (u + v) > 1.0f || t < 0.0f) t = -1.0f;
	return t;
}

float Triangle::Intersect(Ray& ray, glm::vec3& colour, glm::vec3& normal)
{
	float t = Intersect(ray, normal);
	if (t < 0.0f) colour = glm::vec3(0.0f);
	else colour = glm::vec3(0.0f, 1.0f, 0.0f);
	return t;
}

