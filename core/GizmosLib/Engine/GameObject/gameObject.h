#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <GizmosLib/Transforms/Object/transforms.h>
#include <GizmosLib/Engine/Animation/animation.h>
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include <GizmosLib/OpenGL/Core/Mesh/mesh.h>
#include <ew/ewMath/vec2.h>

using namespace GizmosLib::Transforms;
using namespace GizmosLib::OpenGL::Core;

namespace GizmosLib
{
	namespace Engine
	{
		namespace Core
		{
			class GameObject
			{
			public:
				GameObject();

				GameObject(Sprite& sprite, Animation& animation, Mesh& mesh);

				void SetDefaultSprite(Sprite& sprite);

				void SetActiveAnimation(Animation& animation);

				bool Render();

				Transform Transform;

				~GameObject();

			private:
				void Initialize();
				
				void LoadSpriteUV(const std::vector<ew::Vec2>& uv);
				
				Mesh* _mesh;
				Sprite* _defaultSprite;

				Animation* _activeAnimation;
			};
		}
	}
}

#endif