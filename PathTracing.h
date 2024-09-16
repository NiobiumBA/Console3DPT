#pragma once
#include "MathEigen.h"
#include "RenderMaterial.h"
#include "RenderObject.h"
#include "Ray.h"

namespace Graphics::PathTracing
{
    using Eigen::Vector3f;

	Vector3f Reflect(const Vector3f& vec, const Vector3f& normal);
	// The reference on excludeObject needs to avoid hit the object from which this ray was reflected
	bool PathIntersect(const Ray& ray, const RenderObject::VectorObjects& objects, const RenderObject* excludeObject, float maxDistance,
		float& distance, Vector3f& normal, RenderObject*& hitObject);
	Vector3f PathTrace(Ray ray, const RenderObject::VectorObjects& objects, float maxDistance, int maxReflections);
}
