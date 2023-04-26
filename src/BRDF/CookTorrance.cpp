#include "CookTorrance.h"

#include "glm/gtc/constants.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

glm::vec3 CookTorrance(glm::vec3 rayDir, glm::vec3 lightDir, glm::vec3 normal, glm::vec3 albedo, float roughness, float metallic)
{
	glm::vec3 F0 = glm::vec3(0.04f);
	F0 = glm::mix(F0, albedo, metallic);

	glm::vec3 v = -rayDir;
	v = glm::normalize(v);
	lightDir = glm::normalize(lightDir);
	normal = glm::normalize(normal);
	glm::vec3 h = glm::normalize(v + lightDir);

	float D = Dist(normal, h, roughness);
	float G = Geo(normal, v, lightDir, roughness);
	glm::vec3 F = Fresnel(h, v, F0);

	glm::vec3 kd = glm::vec3(1.0f) - F;
	kd *= 1.0f - metallic;

	glm::vec3 diffuse = albedo / glm::pi<float>();
	glm::vec3 specular = (D * G * F) / (4.0f * glm::max(glm::dot(normal, v), 0.00001f) * glm::max(glm::dot(normal, lightDir), 0.00001f));

	return (kd * diffuse + specular);
}

// Fresnel Schlick
inline glm::vec3 Fresnel(glm::vec3 h, glm::vec3 v, glm::vec3 baseReflect)
{
	float hdotv = glm::dot(h, v);
	return baseReflect + (1.0f - baseReflect) * glm::vec3(glm::pow(1.0f - hdotv, 5.0f));
}

// GGX Normal Distribution
float Dist(glm::vec3 n, glm::vec3 h, float roughness)
{
	float ndoth = glm::max(glm::dot(n, h), 0.00001f);
	float roughnessSquared = roughness * roughness;
	roughnessSquared *= roughnessSquared;
	float ndothSquared = ndoth * ndoth;
	float denominator = glm::pi<float>() * glm::pow((ndothSquared * (roughnessSquared - 1.0f) + 1.0f), 2);
	return roughnessSquared / glm::max(denominator, 0.00001f);
}

// Smith's method geometry function
inline float Geo(glm::vec3 n, glm::vec3 v, glm::vec3 l, float roughness)
{
	return SchlickGeo(n, v, roughness) * SchlickGeo(n, l, roughness);
}

inline float SchlickGeo(glm::vec3 n, glm::vec3 v, float roughness)
{
	roughness += 1.0f;
	roughness = (roughness * roughness) / 8.0f;
	float ndotv = glm::max(glm::dot(n, v), 0.00001f);
	return ndotv / (ndotv * (1 - roughness) + roughness);
}
