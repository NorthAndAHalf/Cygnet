#include "Material.h"

Material::Material(glm::vec3 _albedo, float _emittedIntensity)
	: albedo(_albedo), emittedIntensity(_emittedIntensity)
{
}

Material::Material()
	: albedo(glm::vec3(0.0f)), emittedIntensity(0.0f)
{}