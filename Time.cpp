#include "Time.h"

float Time::GetDeltaTime()
{
    return _deltaTime;
}

void Time::Start()
{
    _lastTime = std::chrono::system_clock::now();
}

void Time::Update()
{
    _lastTime = _nowTime;
    _nowTime = std::chrono::system_clock::now();

    std::chrono::duration<double> duration = _nowTime - _lastTime;
    _deltaTime = (float)duration.count();
}
