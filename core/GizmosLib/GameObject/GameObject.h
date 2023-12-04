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

				GameObject();

				void SetShader(ShaderProgram& shader);

				void SetDefaultSprite(Sprite& sprite);

				void SetActiveAnimation(Animation& animation);

				bool Render();

				Transform Transform;

				~GameObject();

			private:
				void Initialize();
				
				void LoadSpriteUV(const std::vector<ew::Vec2>& uv);
				
				Sprite* _defaultSprite;
				ShaderProgram* _attachedShader;

				Animation* _activeAnimation;

				//OpenGL
				unsigned int _VAO;
				unsigned int _VBO;
				unsigned int _EBO;

				std::vector<ew::Vertex> vertices;
				std::vector<unsigned int> indices;

				int _numOfVerts;
				int _numOfIndices;
			};
		}
	}
}

#endif