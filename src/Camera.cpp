#include "Camera.h"
#include "glm/gtc/random.hpp"
#include "glm/vec4.hpp"
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(uint16_t _height, uint16_t _width, glm::vec3 _pos, float _pan, float _tilt, float _focalLength)
    : height(_height), width(_width), position(_pos), pan(_pan), tilt(_tilt), focalLength(_focalLength)
{
	pixelDistance = glm::vec3(2 * (double)1 / (double)width - 1, 2 * (double)1 / (double)height - 1, -focalLength).x - glm::vec3(2 * (double)0 / (double)width - 1, 2 * (double)0 / (double)height - 1, -focalLength).x;
}

Ray Camera::GetSample(uint16_t samples, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy)
{
	float sampleDistance = pixelDistance / samples;
	glm::vec3 pixelCoord = glm::vec3(2 * (double)x / (double)width - 1, 2 * (double)y / (double)height - 1, -focalLength);
	

	glm::vec3 s = glm::vec3(pixelCoord.x + (sampleDistance * sy), pixelCoord.y + (sampleDistance * sx), pixelCoord.z);

	float jitterRange = sampleDistance / 2;
	glm::vec3 jitter = glm::vec3(glm::linearRand(-jitterRange, jitterRange), glm::linearRand(-jitterRange, jitterRange), glm::linearRand(-jitterRange, jitterRange));
	s += jitter;

	glm::vec4 sv4 = glm::vec4(s.s, s.y, s.z, 1.0f);
	sv4 = glm::rotateX(sv4, glm::radians(tilt));
	sv4 = glm::rotateY(sv4, glm::radians(pan));

	s = glm::vec3(sv4.x, sv4.y, sv4.z);
	s += position;

	Ray ray = Ray(glm::vec3(0.0f), glm::normalize(s));
    return ray;
}
