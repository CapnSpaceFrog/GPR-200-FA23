#include "Animation.h"
#include <GLFW/glfw3.h>

Animation::Animation(Sprite sprites[], int size, int fps, float length, bool loop)
{
	_FPS = fps;
	_length = length;
	_loop = loop;
	_startTime = 0.0f;

	for (int i = 0; i < size; i++)
	{
		_sprites.push_back(sprites[i]);
	}

	_timePerSprite = _length / _sprites.size();
	_currentSpriteIndex = 0;

	IsPlaying = false;
}

void Animation::Update()
{
	if (!IsPlaying)
	{
		_startTime = glfwGetTime();
		IsPlaying = true;
		_currentSpriteIndex = 0;
	}

	float timeElapsed = glfwGetTime() - _startTime;

	//All animations will loop since we aren't designing a game engine
	if (timeElapsed > _length && _loop)
	{
		Reset();
		return;
	}

	float spriteFlipTime = timeElapsed - (_timePerSprite * _currentSpriteIndex);

	if (spriteFlipTime > _timePerSprite && _currentSpriteIndex < (_sprites.size() - 1) )
		_currentSpriteIndex++;
}

void Animation::Reset()
{
	_startTime = 0.0f;
	IsPlaying = false;
}