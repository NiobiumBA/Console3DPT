#pragma once
#include "RenderObject.h"
#include "Ray.h"

namespace Graphics::PathTracing
{
	class SphereRender : public Graphics::PathTracing::RenderObject
	{
	public:
		typedef Graphics::PathTracing::RenderObject RenderObject;

		Vector3f position;

		SphereRender(const Vector3f& position, float radius, Material& mat);

		void SetRadius(float radius);
		float GetRadius() const;

		virtual bool RayIntersect(const Ray& ray, float& distance, Vector3f& normal) const override;

	private:
		float _radius;
	};
}
