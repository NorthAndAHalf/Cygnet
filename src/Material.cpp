#include "Material.h"

Material::Material()
	: albedo(glm::vec3(0.0f)), emittedIntensity(0.0f), brdf(0)
{}

Material::Material(glm::vec3 _albedo, float _emittedIntensity, std::shared_ptr<BRDF> _brdf)
	: albedo(_albedo), emittedIntensity(_emittedIntensity), brdf(_brdf)
{}
