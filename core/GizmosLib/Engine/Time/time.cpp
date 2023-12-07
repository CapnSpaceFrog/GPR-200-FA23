#include "time.h"
#include <GLFW/glfw3.h>

using namespace GizmosLib::Engine::Core;

Time::Time()
{
	if (Instance == nullptr)
	{
		Instance = new Time();
		Instance->initialize();
	}
}

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

void Time::initialize()
{
	_prevFrameTime = 0;
	_deltaTime = 0;
	_time = 0;
}