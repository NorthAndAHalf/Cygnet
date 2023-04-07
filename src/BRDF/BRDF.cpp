#include "BRDF.h"
#include "glm/gtc/constants.hpp"

glm::vec3 BRDF::Calculate(const glm::vec3& dir, const glm::vec3& normal, const glm::vec3& albedo) const
{
	return albedo;
}

glm::vec3 DiffuseBRDF::Calculate(const glm::vec3& dir, const glm::vec3& normal, const glm::vec3& albedo) const
{
	return albedo / glm::pi<float>();
}

// When implementing more complex BRDFs, remember to think about ray direction, does thr BRDF expecting an incoming ray or an outgoing ray?
