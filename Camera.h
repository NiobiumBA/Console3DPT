#pragma once
#include "Windows.h"
#include "Eigen/Eigen"
#include "MathEigen.h"

using Eigen::Vector3f;
using Eigen::Matrix4f;
using Eigen::Quaternionf;

class Camera
{
public:
	static inline Camera* main = nullptr;
	
	Vector3f position;
	Quaternionf rotation;


	Camera(float FOV, float aspectRatio, float farClipPlane);
	
	float GetFOV() const;
	void SetFOV(float value);
	float GetAspectRatio() const;
	void SetAspectRatio(float value);
	float GetFarClipPlane() const;
	void SetFarClipPlane(float value);

	Matrix4f CameraToWorld() const;
	Matrix4f WorldToCamera() const;
	Matrix4f ProjectionMatrix() const;
	Matrix4f ViewportToWorld() const;

private:
	float _FOV;
	float _aspectRatio;
	float _farClipPlane;
};
