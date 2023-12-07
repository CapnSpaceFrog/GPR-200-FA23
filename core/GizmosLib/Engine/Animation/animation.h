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
				Animation(Sprite sprites[], int size, int fps, float length, bool loop);

				void Update();

				void Reset();

				bool IsPlaying;

			private:
				std::vector<Sprite> _sprites;

				int _FPS;
				float _length;
				bool _loop;

				float _timePerSprite;
				int _currentSpriteIndex;

				float _startTime;
			};
		}
	}
}

#endif