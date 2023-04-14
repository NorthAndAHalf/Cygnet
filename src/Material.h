#pragma once

#include "glm/vec3.hpp"
#include "BRDF/BRDF.h"
#include <memory>

struct Material
{
	Material();
	Material(glm::vec3 _albedo, float _emittedIntensity, std::shared_ptr<BRDF> _brdf);

	glm::vec3 albedo;
	float emittedIntensity;
	std::shared_ptr<BRDF> brdf;
};
