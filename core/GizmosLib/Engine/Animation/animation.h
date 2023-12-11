#ifndef _ANIMATION_
#define _ANIMATION_

#include <GizmosLib/OpenGL/Core/Sprites/sprite.h>
#include <vector>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class Animation
			{
			public:
				Animation();

				Animation(Sprite* sprites[], int size, int fps, float length, bool loop);

				void Update();

				void SetLength(float length);

				void SetFPS(int fps);

				Sprite& GetCurrentSprite();

				void Reset();

			private:
				std::vector<Sprite*> _sprites;
				Sprite* _currentSprite;

				float _framesPerSprite;
				float _length;
				float _timeLastFrame;

				int _FPS;
				int _totalFrameCount;
				int _spriteFrameCount;
				int _currentSpriteIndex;
				int _numOfSprites;
				
				bool _loop;
				bool _isPlaying;

				double _secForFrame;
			};
		}
	}
}

#endif