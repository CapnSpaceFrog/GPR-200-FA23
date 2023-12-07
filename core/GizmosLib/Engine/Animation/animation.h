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
				Animation(Sprite* sprites[], int size, int fps, float length, bool loop);

				void Update();

				Sprite& GetCurrentSprite();

				void Reset();

			private:
				std::vector<Sprite*> _sprites;
				Sprite* _currentSprite;

				int _FPS;
				float _length;

				int _framesPerSprite;
				int _frameCount;
				int _currentSpriteIndex;
				
				bool _loop;
				bool _isPlaying;

				double _secForFrame;
				float _timeLastFrame;
			};
		}
	}
}

#endif