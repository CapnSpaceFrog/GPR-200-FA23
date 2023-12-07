#ifndef _SPRITE_
#define _SPRITE_

#include <GizmosLib/OpenGL/Core/Texture/texture.h>
#include <GizmosLib/OpenGL/Core/Mesh/mesh.h>
#include <ew/ewMath/ewMath.h>
#include <vector>

using namespace GizmosLib::OpenGL::Core;

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

				bool Render(Mesh& mesh);

			private:
				Texture* _tex;
				ew::Vec2 _sourceXY;
				int _pixels;

				std::vector<ew::Vec2> UV;
			};
		}
	}
}

#endif