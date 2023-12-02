#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <GizmosLib/Transforms/Object/transforms.h>
#include <GizmosLib/Animation/Animation.h>
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include <ew/ewMath/vec2.h>

using namespace GizmosLib::Math;
using namespace GizmosLib::Transforms;
using namespace GizmosLib::OpenGL::Core;

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class GameObject
			{
			public:
				Transform Transform;

				Sprite Sprite;

				GameObject(int uvCornerX, int uvCornerY, int width, int height);

				bool Draw();

				bool SwapActiveAnimation(Animation::AnimationTypes animType);

			private:

				Animation::Animation* activeAnim;

				Animation::Animation anims[Animation::AnimationTypes::Max];
			};
		}
	}
}

#endif