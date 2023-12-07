#include "Animation.h"
#include <GizmosLib/Engine/Time/time.h>
#include <GizmosLib/OpenGL/Core/Sprites/sprite.h>
#include <GLFW/glfw3.h>

using namespace GizmosLib::Engine::Core;

Animation::Animation(Sprite* sprites[], int size, int fps, float length, bool loop)
{
	_FPS = fps;
	_length = length;
	_loop = loop;

	for (int i = 0; i < size; i++)
	{
		_sprites.push_back(sprites[i]);
	}

	_framesPerSprite = (_length * _FPS) ;

	_isPlaying = false;

	_currentSprite = sprites[0];

	_secForFrame = 1.0f / _FPS;

	_frameCount = 0;
	_currentSpriteIndex = 0;
}

void Animation::Update()
{
	if (!_isPlaying)
	{
		_isPlaying = true;
		_timeLastFrame = 0;
		_frameCount = 0;
		_currentSpriteIndex = 0;
	}

	_timeLastFrame += Time::GetDeltaTime();

	//We only want to update the animation based on our FPS, so check to make sure we should update
	if (_timeLastFrame < _secForFrame)
		return;

	//Is the animation finished?
	if ((_frameCount > (_FPS * _length)) && _loop)
	{
		Reset();
		return;
	}

	//Update the sprite if we have cycled through the number of frames per sprite
	if (_frameCount % _framesPerSprite == 0)
	{
		_currentSpriteIndex++;
		_currentSprite = _sprites[_currentSpriteIndex];
		_currentSprite->Render();
	}
	
	_timeLastFrame = 0;
	_frameCount++;
}

Sprite& Animation::GetCurrentSprite()
{
	return *_currentSprite;
}

void Animation::Reset()
{
	_isPlaying = false;
}