#include "RayHit.h"

RayHit::RayHit(Ray _ray, glm::vec3 _pos, glm::vec3 _normal, Material _mat, float _t)
	: ray(_ray), pos(_pos), normal(_normal), mat(_mat), t(_t)
{

}

RayHit::RayHit()
	: ray(Ray(glm::vec3(0.0f), glm::vec3(0.0f))), pos(glm::vec3(0.0f)), normal(glm::vec3(0.0f)), mat(Material(glm::vec3(0.0f), 0.0f)), t(-1.0f)
{}
