#ifndef GL_HELPERS
#define GL_HELPERS

#include <string>
#include <ew/ewMath/ewMath.h>
#include <external/glad.h>
#include <GLFW/glfw3.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Utility
		{
			extern int SCREEN_WIDTH;
			extern int SCREEN_HEIGHT;
			
			
			unsigned int generateVAO(float* vertData, int numOfVerts, unsigned int* indicesData, int numIndices);

			void framebufferSizeCallback(GLFWwindow* window, int width, int height);

			unsigned int loadTexture(const char* filePath, GLenum minFilterMode, GLenum magFilterMode, GLenum horWrapMode, GLenum vertWrapMode);
		}
	}
}

#endif