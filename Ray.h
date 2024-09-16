#pragma once
#include "Eigen/Eigen"

namespace Graphics::PathTracing
{
	using Eigen::Vector3f;

	struct Ray
	{
		Vector3f origin;
		Vector3f direction;
	};
}
