#pragma once

#include "glm/vec3.hpp"

struct BRDF
{
	glm::vec3 Calculate(const glm::vec3& outDir, const glm::vec3& normal, const glm::vec3& inDir, const glm::vec3& albedo) const;
};