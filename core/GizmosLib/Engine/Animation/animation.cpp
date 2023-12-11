#include "Animation.h"
#include <GizmosLib/Engine/Time/time.h>
#include <GizmosLib/OpenGL/Core/Sprites/sprite.h>
#include <GLFW/glfw3.h>

using namespace GizmosLib::Engine::Core;

Animation::Animation() {}

Animation::Animation(Sprite* sprites[], int size, int fps, float length, bool loop)
{
	_FPS = fps;
	_length = length;
	_loop = loop;
	_numOfSprites = size;

	for (int i = 0; i < _numOfSprites; i++)
		_sprites.push_back(sprites[i]);

	_isPlaying = false;

	_framesPerSprite = (_length * _FPS) / _numOfSprites;

	_currentSprite = sprites[0];

	_secForFrame = 1.0f / _FPS;
	_currentSpriteIndex = 0;
	_spriteFrameCount = 0;
	_totalFrameCount = 0;
	_timeLastFrame = 0;
}

void Animation::Update()
{
	if (!_isPlaying)
		_isPlaying = true;

	_timeLastFrame += Time::GetDeltaTime();

	//We only want to update the animation based on our FPS, so check to make sure we should update
	if (_timeLastFrame < _secForFrame)
		return;

	_totalFrameCount++;
	_spriteFrameCount++;

	//Is the animation finished?
	if ((_totalFrameCount >= (_FPS * _length)) && _loop)
	{
		Reset();
		return;
	}

	//Update the sprite if we have cycled through the number of frames per sprite
	if (_spriteFrameCount >= _framesPerSprite)
	{
		_currentSpriteIndex++;
		_currentSprite = _sprites[_currentSpriteIndex];
		_spriteFrameCount = 0;
	}

	_timeLastFrame = 0;
}

void Animation::SetLength(float length)
{
	_length = length;

	_framesPerSprite = (_length * _FPS) / _numOfSprites;

	Reset();
}

void Animation::SetFPS(int fps)
{
	_FPS = fps;

	_framesPerSprite = (_length * _FPS) / _numOfSprites;
	_secForFrame = 1.0f / _FPS;

	Reset();
}

Sprite& Animation::GetCurrentSprite()
{
	return *_currentSprite;
}

void Animation::Reset()
{
	_isPlaying = false;

	_currentSpriteIndex = 0;
	_spriteFrameCount = 0;
	_totalFrameCount = 0;
	
	_timeLastFrame = 0;
	
	_currentSprite = _sprites[0];
}