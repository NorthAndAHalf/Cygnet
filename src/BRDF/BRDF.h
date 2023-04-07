#pragma once

#include "glm/vec3.hpp"

struct BRDF
{
	virtual glm::vec3 Calculate(const glm::vec3& dir, const glm::vec3& normal, const glm::vec3& albedo) const;
};

struct DiffuseBRDF : public BRDF
{
	DiffuseBRDF() {}
	virtual glm::vec3 Calculate(const glm::vec3& dir, const glm::vec3& normal, const glm::vec3& albedo) const override;
};