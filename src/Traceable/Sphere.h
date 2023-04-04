#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere(glm::vec3 _origin, float _radius);

	virtual RayHit Intersect(const Ray& ray);
	virtual void ApplyMaterial(Material _mat) override;
private:
	glm::vec3 centre;
	float radius;
	Material mat;
};