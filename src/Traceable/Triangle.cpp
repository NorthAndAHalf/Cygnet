#include "Triangle.h"
#include "glm/geometric.hpp"

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	: P1(p1), P2(p2), P3(p3)
{
}

glm::vec3 Triangle::Trace(Ray& ray)
{
	glm::vec3 surfaceContribution;
	float t = Intersect(ray, surfaceContribution);

	// Step 1: Recursively reflect rays by sampling the BRDF (I guess MIS will be implemented here)
	// Step 2: Combine all colours reflected rays colours into one reflection contribution
	// Step 3: Combine surfaceContribution with reflection contribution
	// Step 4: Return final colour

	glm::vec3 reflectedContribution = glm::vec3(0.8f); // Temporary, just so I can get a sphere rendering atm

	// idk how the colours are combined atm. Here I'm giving them equal weighting but I don't know
	// how it is done in the rendering equation
	glm::vec3 output = (surfaceContribution * reflectedContribution);
	return output;
}

float Triangle::Intersect(Ray& ray)
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

float Triangle::Intersect(Ray& ray, glm::vec3& colour)
{
	float t = Intersect(ray);
	if (t < 0.0f) colour = glm::vec3(0.0f);
	else colour = glm::vec3(0.0f, 1.0f, 0.0f);
	return t;
}

