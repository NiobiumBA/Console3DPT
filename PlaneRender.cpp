#include "PlaneRender.h"

Graphics::PathTracing::PlaneRender::PlaneRender(const Vector3f& normal, float distance, Material& material)
	: distance(distance)
{
	this->material = &material;
	SetNormal(normal);
}

void Graphics::PathTracing::PlaneRender::SetNormal(const Vector3f& normal)
{
	_normal = normal.normalized();
}

Eigen::Vector3f Graphics::PathTracing::PlaneRender::GetNormal() const
{
	return _normal;
}

bool Graphics::PathTracing::PlaneRender::RayIntersect(const Ray& ray, float& distance, Vector3f& normal) const
{
	normal = _normal;
	distance = -(ray.origin.dot(_normal) + this->distance) / ray.direction.dot(_normal);

	return distance > 0;
}
