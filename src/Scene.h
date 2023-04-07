#pragma once

#include "glm/vec3.hpp"
#include "Traceable/Traceable.h"

class Scene
{
	Scene(std::vector<Traceable*>* _traceables);

	void SetTraceables(std::vector<Traceable*>* _traceables);
	const std::vector<Traceable*>* GetTraceables() const;
private:
	std::vector<Traceable*>* traceables;
};
