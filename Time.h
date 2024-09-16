#pragma once
#include <chrono>

class Time
{
	typedef std::chrono::system_clock::time_point point;

public:
	static void Start();
	static void Update();
	static float GetDeltaTime();

private:
	static inline float _deltaTime;
	static inline point _lastTime;
	static inline point _nowTime;
};

