#pragma once

#include "glm/vec3.hpp"
#include "Traceable/Traceable.h"
#include "RayHit.h"

class Scene
{
public:
	Scene(std::vector<Traceable*>* _traceables);

	void SetTraceables(std::vector<Traceable*>* _traceables);
	const std::vector<Traceable*>* GetTraceables() const;

	RayHit Intersect(const Ray& ray, uint8_t bounces) const;

private:
	std::vector<Traceable*>* traceables;
};
