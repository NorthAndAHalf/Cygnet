#pragma once
#include "pch.h"
#include "Ray.h"
#include "RayHit.h"
#include "Material.h"

class Primitive
{
public:
	virtual RayHit Intersect(const Ray& ray) = 0;
	virtual float IntersectTest(const Ray& ray) = 0;
	virtual void ApplyMaterial(Material* _mat) = 0;
};