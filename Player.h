#pragma once
#include "Camera.h"
#include "Behaviour.h"

using Eigen::Vector4f;
using Eigen::Vector2f;
using Eigen::AngleAxisf;

class Player : virtual public Behaviour
{
public:
	Camera& camera;

	Player(Camera& cam);

	virtual void Update() override;

	void SetPosition(const Vector3f& pos);
	Vector3f GetPosition() const;

	void Rotate(const Vector3f& eulerAnglesDelta);
	Vector3f GetEulerAngles() const;

private:
	float _speed;
	float _sensitivity;
	Vector3f _position;
	Vector3f _eulerAngles;

	void Movement();
	void Rotate();
};
