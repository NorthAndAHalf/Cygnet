#pragma once
#include "glm/vec3.hpp"

class Ray
{
public:
	Ray(glm::vec3 _origin, glm::vec3 _dir);
	glm::vec3 At(float t) const;

	glm::vec3 origin;
	glm::vec3 direction;
};