#pragma once

#include "glm/vec3.hpp"

struct BRDF
{
	BRDF(float _roughness, float _metallic);

	glm::vec3 Calculate(const glm::vec3& rayDir, const glm::vec3& normal, const glm::vec3& lightDir, const glm::vec3& albedo) const;

	float roughness;
	float metallic;
};