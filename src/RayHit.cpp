#include "RayHit.h"

RayHit::RayHit(glm::vec3 _pos, glm::vec3 _incident, glm::vec3 _normal, glm::vec3 _surface, float _emissive, float _t, int _depth)
	: pos(_pos), incident(_incident), normal(_normal), surface(_surface), emissive(_emissive), t(_t), depth(_depth)
{

}

RayHit::RayHit()
	: pos(glm::vec3(0.0f)), incident(glm::vec3(0.0f)), normal(glm::vec3(0.0f)), surface(glm::vec3(0.0f)), emissive(0.0f), t(-1.0f), depth(-1)
{}