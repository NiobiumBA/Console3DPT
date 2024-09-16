#pragma once
#include "RenderObject.h"

namespace Graphics::PathTracing
{
	class PlaneRender : public RenderObject
	{
	public:
		// The distance measured from the Plane to the origin, along the Plane's normal.
		float distance;

		PlaneRender(const Vector3f& normal, float distance, Material& material);

		void SetNormal(const Vector3f& normal);
		Vector3f GetNormal() const;

		virtual bool RayIntersect(const Ray& ray, float& distance, Vector3f& normal) const override;
	private:
		Vector3f _normal;
	};
}

