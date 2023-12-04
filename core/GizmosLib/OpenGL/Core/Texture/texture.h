#ifndef _TEXTURE_
#define _TEXTURE_

#include <GLFW/glfw3.h>
#include <vector>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class Texture
			{
			public:

				Texture(const char* filePath, GLenum minFilterMode, GLenum magFilterMode, GLenum wrapMode);

				void UpdateTexPath(const char* filePath);

				void UpdateWrapMode(GLenum wrapMode);

				void UpdateMinFilter(GLenum minFilter);

				void UpdateMagFilter(GLenum magFilter);

				unsigned int TextureID;
				int Width, Height;

			private:
				bool loadTexture(const char* filePath, GLenum minFilterMode, GLenum magFilterMode, GLenum wrapMode);

				GLenum _wrapMode;
				GLenum _minFilterMode;
				GLenum _magFilterMode;
			};
		}
	}
}

#endif