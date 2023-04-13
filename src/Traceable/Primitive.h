#pragma once
#include "pch.h"
#include "Ray.h"
#include "RayHit.h"
#include "Material.h"

class Primitive
{
public:
	virtual RayHit Intersect(const Ray& ray) = 0;
	virtual void ApplyMaterial(std::shared_ptr<Material> _mat) = 0;
};