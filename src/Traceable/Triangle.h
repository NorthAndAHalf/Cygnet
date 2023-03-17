#pragma once

#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	virtual RayHit Trace(Ray& ray, uint8_t depth) override;
	virtual float Intersect(Ray& ray) override;
	virtual float Intersect(Ray& ray, glm::vec3& normal) override;
	virtual float Intersect(Ray& ray, glm::vec3& colour, glm::vec3& normal) override;
private:
	glm::vec3 P1;
	glm::vec3 P2;
	glm::vec3 P3;
};