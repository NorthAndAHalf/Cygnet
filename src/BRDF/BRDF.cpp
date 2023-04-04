#include "BRDF/Diffuse.h"
#include "glm/gtc/constants.hpp"

glm::vec3 BRDF::Diffuse(const glm::vec3& albedo)
{
	return albedo / glm::pi<float>();
}
