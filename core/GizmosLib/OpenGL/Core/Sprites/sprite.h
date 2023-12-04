#ifndef _SPRITE_
#define _SPRITE_

#include "GizmosLib/OpenGL/Core/Shaders/shaderProgram.h"
#include <ew/mesh.h>
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

				Sprite(ew::Vec2 spriteSheetCorner, ew::Vec2 texDimensions, int pixels, unsigned int tex);

				void SetBoundTexture(unsigned int texID);

				unsigned int GetBoundTex() { return _TEX; }

				std::vector<ew::Vec2> UV;

			private:
				unsigned int _TEX;

				ew::Vec2 _corner;
				ew::Vec2 _texDimensions;
				int _pixelDimensions;
			};
		}
	}
}

#endif