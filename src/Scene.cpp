#include "Scene.h"

Scene::Scene(std::vector<Traceable*>* _traceables)
	: traceables(_traceables)
{}

void Scene::SetTraceables(std::vector<Traceable*>*_traceables)
{
	traceables = _traceables;
}

const std::vector<Traceable*>* Scene::GetTraceables() const
{
	return traceables;
}

RayHit Scene::Intersect(const Ray& ray) const
{
	return RayHit();
}
