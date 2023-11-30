#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <GizmosLib/Math/transformations.h>
#include <GizmosLib/Animation/Animation.h>
#include <ew/ewMath/vec2.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace GameObject
		{
			class GameObject
			{
			public:

				GameObject(int uvCornerX, int uvCornerY, int width, int height);

				bool Draw();

				bool SwapActiveAnimation(Animation::AnimationTypes animType);

			private:

				GizmosLib::Math::Transform::Transform transform;

				Animation::Animation* activeAnim;

				Animation::Animation anims[Animation::AnimationTypes::Max];
			};
		}
	}
}

#endif