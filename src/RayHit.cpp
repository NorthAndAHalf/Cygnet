#include "RayHit.h"

RayHit::RayHit(Ray _ray, glm::vec3 _pos, glm::vec3 _normal, Material _mat, float _t)
	: ray(_ray), pos(_pos), normal(_normal), mat(_mat), t(_t)
{

}

RayHit::RayHit()
	: ray(Ray(glm::vec3(0.0f), glm::vec3(0.0f))), pos(glm::vec3(0.0f)), normal(glm::vec3(0.0f)), mat(Material()), t(-1.0f)
{}

glm::vec3 RayHit::BRDFCalculate() const
{
	return mat.brdf.Calculate(ray.direction, normal, mat.albedo);
}
