#include "RayHit.h"

RayHit::RayHit(glm::vec3 _pos, glm::vec3 _rayDir, glm::vec3 _normal, Material _mat, float _t, glm::vec3 _outColor)
	: pos(_pos), rayDir(_rayDir), normal(_normal), mat(Material(glm::vec3(1.0f), 1.0f)), t(_t), outColour(_outColor)
{

}

