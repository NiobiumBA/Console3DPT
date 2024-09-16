#pragma once
#include "Eigen/Eigen"

namespace Graphics::PathTracing
{
	using Eigen::Vector3f;

	struct Material
	{
		Vector3f emittance;
		Vector3f reflectance;
		float roughness;
	};
}
