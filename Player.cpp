#include "Player.h"
#include "Input.h"
#include "Time.h"

Player::Player(Camera& cam) : camera(cam)
{
	_speed = 1;
	_sensitivity = 1.3f;
	_eulerAngles = Vector3f::Zero();
	SetPosition(Vector3f::Zero());
}

void Player::Update()
{
	Movement();

	Rotate();
}

void Player::Movement()
{
	float horizontalAxis = Input::GetVirtualAxis('d', 'a');
	float verticalAxis = Input::GetVirtualAxis('s', 'w');
	float upAxis = Input::GetVirtualAxis('e', 'q');

	Vector2f localMove = Vector2f(horizontalAxis, verticalAxis);
	localMove.normalize();
	localMove *= _speed * Time::GetDeltaTime();

	Matrix4f rotation = MathEigen::QuaternionToMatrix4f(MathEigen::EulerToQuaternion(Vector3f(0, _eulerAngles.y(), 0)));
	Vector4f worldMove = rotation * Vector4f(localMove.x(), 0, localMove.y(), 1);

	float upMove = _speed * Time::GetDeltaTime() * upAxis;

	SetPosition(_position + Vector3f(worldMove.x(), upMove, worldMove.z()));
}

void Player::Rotate()
{
	float horizontalAxis = Input::GetVirtualAxis(Input::Key::ArrowLeft, Input::Key::ArrowRight);
	float verticalAxis = Input::GetVirtualAxis(Input::Key::ArrowUp, Input::Key::ArrowDown);

	Vector3f rotationDelta = Time::GetDeltaTime() * _sensitivity * Vector3f(verticalAxis, horizontalAxis, 0);

	Rotate(rotationDelta);
}

void Player::SetPosition(const Vector3f& pos)
{
	_position = pos;
	camera.position = pos;
}

Vector3f Player::GetPosition() const
{
	return _position;
}

void Player::Rotate(const Vector3f& eulerAnglesDelta)
{
	_eulerAngles += eulerAnglesDelta;

	_eulerAngles = Vector3f(std::clamp(_eulerAngles.x(), -(float)M_PI_2, (float)M_PI_2), 
							std::fmod(_eulerAngles.y(), 2 * (float)M_PI),
							std::fmod(_eulerAngles.z(), 2 * (float)M_PI));

	camera.rotation = MathEigen::EulerToQuaternion(_eulerAngles);

	//camera.rotation.normalize();
}

Vector3f Player::GetEulerAngles() const
{
	return _eulerAngles;
}
