#include "Material.h"

Material::Material()
	: albedo(glm::vec3(0.0f)), emittedIntensity(0.0f), brdf(std::shared_ptr<BRDF>(new BRDF()))
{}

Material::Material(glm::vec3 _albedo, float _emittedIntensity, std::shared_ptr<BRDF>& _brdf)
	: albedo(_albedo), emittedIntensity(_emittedIntensity), brdf(_brdf)
{}
