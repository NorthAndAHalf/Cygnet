#pragma once
#include "Primitive.h"

class Sphere : Primitive
{
public:
	Sphere(glm::vec3 _origin, float _radius);

	virtual glm::vec3 Trace(Ray& ray) override;
	virtual float Intersect(Ray& ray) override;
	virtual float Intersect(Ray& ray, glm::vec3& colour) override;
private:
	glm::vec3 centre;
	float radius;
};