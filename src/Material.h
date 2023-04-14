#pragma once

#include "glm/vec3.hpp"
#include "BRDF/BRDF.h"
#include <memory>

struct Material
{
	Material();
	Material(glm::vec3 _albedo, float _emittedIntensity, BRDF* _brdf);

	glm::vec3 albedo;
	float emittedIntensity;
	BRDF* brdf;
};
