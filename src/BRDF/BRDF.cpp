#include "BRDF.h"
#include "glm/gtc/constants.hpp"
#include "CookTorrance.h"

BRDF::BRDF(float _roughness, float _metallic)
	: roughness(_roughness), metallic(_metallic)
{}

glm::vec3 BRDF::Calculate(const glm::vec3& rayDir, const glm::vec3& normal, const glm::vec3& lightDir, const glm::vec3& albedo) const
{
	return CookTorrance(rayDir, lightDir, normal, albedo, roughness, metallic);
}
