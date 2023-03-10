#include "Ray.h"

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
	: origin(_origin), direction(_direction)
{

}

glm::vec3 Ray::At(float t)
{
	return origin + (t * direction);
}