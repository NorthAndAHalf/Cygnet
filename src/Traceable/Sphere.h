#pragma once
#include "Primitive.h"

class Sphere : public Primitive
{
public:
	Sphere(glm::vec3 _origin, float _radius);

	virtual RayHit Trace(Ray& ray, uint8_t depth) override;
	virtual float Intersect(Ray& ray, glm::vec3& normal) override;
	virtual float Intersect(Ray& ray, glm::vec3& colour, glm::vec3& normal) override;
private:
	glm::vec3 centre;
	float radius;
};