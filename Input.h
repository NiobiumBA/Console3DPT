#pragma once
#include <conio.h>
#include <iostream>

class Input
{
public:
	enum Key
	{
		Escape = 27,
		Tab = 9,
		Backspace = 8,
		Enter = 13,
		Insert = -82,
		Delete = -83,
		Home = -71,
		End = -79,
		PageUp = -73,
		PageDown = -81,
		ArrowUp = -72,
		ArrowDown = -80,
		ArrowLeft = -75,
		ArrowRight = -77
	};

	static void Start();
	static void Update();
	static void Clear();
	static bool GetKeyPress(char key);
	static bool GetKeyDown(char key);
	static bool GetKeyUp(char key);
	static bool IsShift();
	static float GetVirtualAxis(char positiveKey, char negativeKey);
	static char GetInput();

private:
	static inline char _input;
	static inline char _lastInput;
	static inline bool _isShift;
};

