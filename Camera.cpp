#include "Camera.h"

Camera::Camera(float FOV, float aspectRatio, float farClipPlane)
{
	if (main == nullptr)
		main = this;

	_FOV = std::clamp(FOV, 1.0f, 179.0f);
	_aspectRatio = std::max(aspectRatio, 0.001f);
	_farClipPlane = std::max(1.0f, farClipPlane);
	
	position = Vector3f::Zero();
	rotation = Quaternionf::Identity();
}

float Camera::GetFOV() const
{
	return _FOV;
}

void Camera::SetFOV(float value)
{
	_FOV = std::clamp(value, 1.0f, 179.0f);
}

float Camera::GetAspectRatio() const
{
	return _aspectRatio;
}

void Camera::SetAspectRatio(float value)
{
	_aspectRatio = std::max(value, 0.001f);
}

float Camera::GetFarClipPlane() const
{
	return _farClipPlane;
}

void Camera::SetFarClipPlane(float value)
{
	_farClipPlane = std::max(1.0f, value);
}

Matrix4f Camera::CameraToWorld() const
{
	Matrix4f offset = MathEigen::TranslationMatrix4f(position);

	Matrix4f rot4 = MathEigen::QuaternionToMatrix4f(rotation);

	return offset * rot4;
	//return Matrix4f::Identity();
}

Matrix4f Camera::WorldToCamera() const
{
	Matrix4f offset = MathEigen::TranslationMatrix4f(-position);

	Eigen::Matrix4f rot4 = MathEigen::QuaternionToMatrix4f(rotation.conjugate());

	return rot4 * offset;
}

Matrix4f Camera::ProjectionMatrix() const
{
	float fovRadians = _FOV * MathEigen::DegToRad;
	
	// Must convert to cotangent
	float scaleXY = (1.0f / std::tan(fovRadians * 0.5f));

	Matrix4f result = Matrix4f::Identity();
	result(0, 0) = scaleXY / _aspectRatio;
	result(1, 1) = scaleXY;

	return result;
}

Matrix4f Camera::ViewportToWorld() const
{
	return (ProjectionMatrix() * WorldToCamera()).inverse();
}
