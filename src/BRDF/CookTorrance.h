#pragma once

#include "glm/vec3.hpp"

glm::vec3 CookTorrance(glm::vec3 rayDir, glm::vec3 lightDir, glm::vec3 normal, glm::vec3 albedo, float roughness, float metallic);

float Dist(glm::vec3 n, glm::vec3 h, float roughness);
inline float Geo(glm::vec3 n, glm::vec3 v, glm::vec3 l, float roughness);
inline float SchlickGeo(glm::vec3 n, glm::vec3 v, float roughness);
inline glm::vec3 Fresnel(glm::vec3 h, glm::vec3 v, glm::vec3 baseReflect);
float GGXpdf(glm::vec3 wi, glm::vec3 wo, float roughness);