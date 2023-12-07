#ifndef _SPRITE_
#define _SPRITE_

#include <GizmosLib/OpenGL/Core/Texture/texture.h>
#include <GizmosLib/Transforms/Object/transforms.h>
#include <GizmosLib/OpenGL/Core/Mesh/mesh.h>
#include <ew/ewMath/ewMath.h>
#include <vector>

using namespace GizmosLib::OpenGL::Core;
using namespace GizmosLib::Transforms;

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class Sprite
			{
			public:

				Sprite(Texture& tex, ew::Vec2 sourceXY, int pixels);

				void SetBoundTex(Texture& tex);

				Texture& GetBoundTex();

				bool Render(Transform& transform);

				Mesh BoundMesh;
			private:
				Texture* _tex;
				ew::Vec2 _sourceXY;
				int _pixels;
			};
		}
	}
}

#endif