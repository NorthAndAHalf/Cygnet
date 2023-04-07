#include "Material.h"

Material::Material()
	: albedo(glm::vec3(0.0f)), emittedIntensity(0.0f), brdf(DiffuseBRDF())
{}

Material::Material(glm::vec3 _albedo, float _emittedIntensity, BRDF _brdf)
	: albedo(_albedo), emittedIntensity(_emittedIntensity), brdf(_brdf)
{
}
