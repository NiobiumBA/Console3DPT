#include "MathEigen.h"

Eigen::Quaternionf MathEigen::EulerToQuaternion(const Vector3f& eulerAngles)
{
	return AngleAxisf(eulerAngles.z(), Vector3f::UnitZ()) *
			AngleAxisf(eulerAngles.y(), Vector3f::UnitY()) *
			AngleAxisf(eulerAngles.x(), Vector3f::UnitX());
}

Eigen::Matrix4f MathEigen::QuaternionToMatrix4f(const Quaternionf& q)
{
	Eigen::Matrix3f rot3 = q.toRotationMatrix();

	Matrix4f rot4 = Matrix4f::Identity();

	for (size_t x = 0; x < 3; x++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			rot4.coeffRef(x, y) = rot3.coeffRef(x, y);
		}
	}

	return rot4;
}

Eigen::Matrix4f MathEigen::TranslationMatrix4f(const Vector3f& translation)
{
	Matrix4f result = Matrix4f::Identity();
	result.coeffRef(0, 3) = translation.x();
	result.coeffRef(1, 3) = translation.y();
	result.coeffRef(2, 3) = translation.z();

	return result;
}
