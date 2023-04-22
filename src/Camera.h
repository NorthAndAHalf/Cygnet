#pragma once

#include "glm/vec3.hpp"
#include "Ray.h"

class Camera
{
public:
	Camera(uint16_t _height, uint16_t _width, glm::vec3 _pos, float _pan, float _tilt, float _focalLength);

	Ray GetSample(uint16_t samples, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy);

	uint16_t height;
	uint16_t width;
	glm::vec3 position;
	float pan;
	float tilt;
	float focalLength;
private:
	float pixelDistance;
};
