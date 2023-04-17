#pragma once

#include "glm/vec3.hpp"
#include "Ray.h"
#include <vector>
#include "Traceable/Traceable.h"
#include "RayHit.h"
#include "Scene.h"

glm::vec3 Trace(const RayHit& hitPoint, const std::vector<Traceable*>& traceables, uint8_t depth, uint8_t limit);
glm::vec3 TracePath(Ray ray, const Scene& scene, uint8_t bounces);
glm::vec3 DebugTrace(Ray ray, const Scene& scene);

RayHit IntersectTraceables(const Ray& ray, const std::vector<Traceable*>& traceables);
