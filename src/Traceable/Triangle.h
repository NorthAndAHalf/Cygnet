#pragma once

#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	virtual RayHit Intersect(const Ray& ray);
	virtual void ApplyMaterial(Material _mat) override;
private:
	glm::vec3 P1;
	glm::vec3 P2;
	glm::vec3 P3;

	Material mat;
};