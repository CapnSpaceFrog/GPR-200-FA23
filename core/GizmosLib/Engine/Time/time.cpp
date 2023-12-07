#include "time.h"
#include <GLFW/glfw3.h>

using namespace GizmosLib::Engine::Core;

float Time::_deltaTime = 0;
float Time::_prevFrameTime = 0;
float Time::_time = 0;

void Time::Update()
{
	_time = (float)glfwGetTime();

	_deltaTime = _time - _prevFrameTime;

	_prevFrameTime = _time;
}

float Time::GetTime()
{
	return _time;
}

float Time::GetDeltaTime()
{
	return _deltaTime;
}