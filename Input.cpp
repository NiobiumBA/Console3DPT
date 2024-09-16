#include "Input.h"

void Input::Start()
{
	_input = 0;
	_lastInput = 0;
	_isShift = false;
}

void Input::Update()
{
	_lastInput = _input;
	
	_input = _getch();

	if (_input == -32)
		_input = -_getch();

	_isShift = _input >= 0 ? std::isupper(_input) : false;
	if (_input >= 0)
		_input = std::tolower(_input);
}

void Input::Clear()
{
	Start();
}

bool Input::GetKeyPress(char key)
{
	return _input == key;
}

bool Input::GetKeyDown(char key)
{
	return _lastInput != key && _input == key;
}

bool Input::GetKeyUp(char key)
{
	return _lastInput == key && _input != key;
}

bool Input::IsShift()
{
	return _isShift;
}

float Input::GetVirtualAxis(char positiveKey, char negativeKey)
{
	float axis;

	if (Input::GetKeyPress(positiveKey))
		axis = 1;
	else if (Input::GetKeyPress(negativeKey))
		axis = -1;
	else
		axis = 0;

	return axis;
}

char Input::GetInput()
{
	return _input;
}
