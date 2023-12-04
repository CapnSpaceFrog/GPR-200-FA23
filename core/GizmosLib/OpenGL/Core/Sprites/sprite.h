#ifndef _SPRITE_
#define _SPRITE_

#include <GizmosLib/OpenGL/Core/Texture/texture.h>
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

				void SetBoundTex(unsigned int texID);

				unsigned int GetBoundTex();

				bool Render();

				std::vector<ew::Vec2> UV;

			private:
				Texture* _tex;
				ew::Vec2 _sourceXY;
				int _pixels;
			};

			struct SpriteData
			{
				ew::Vec3 VertPos;
				ew::Vec2 spriteTexCorner;
				ew::Vec2 texSize;
			};
		}
	}
}

#endif