#pragma once
#include <algorithm>
#include "MathEigen.h"
#include "Behaviour.h"
#include "RenderMaterial.h"
#include "Ray.h"

namespace Graphics::PathTracing
{
	using Eigen::Vector2f;
	using Eigen::Vector3f;
	using Eigen::Matrix3f;

	class RenderObject : public Behaviour
	{
	public:
		typedef std::vector<RenderObject*> VectorObjects;

		Material* material;

		static VectorObjects& GetRenderObjects();

		void OnEnable() override;
		void OnDisable() override;

		virtual bool RayIntersect(const Ray& ray, float& distance, Vector3f& normal) const { return false; };
	};
}
