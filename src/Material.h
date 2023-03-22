#pragma once

#include "glm/vec3.hpp"

struct Material
{
	Material(glm::vec3 _albedo, float _emittedIntensity);

	glm::vec3 albedo;
	float emittedIntensity;
	// BRDF once implemented
	// Diffuse brdf = albedo / pi
};