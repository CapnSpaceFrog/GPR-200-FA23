#ifndef GL_HELPERS
#define GL_HELPERS

#include <string>
#include <external/glad.h>
#include <GLFW/glfw3.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		const std::string vertFilePath = "Assets/BasicVertex.vert";
		const std::string fragFilePath = "Assets/BasicFrag.frag";

		unsigned int generateVAO(float* vertData, int numOfVerts, unsigned int* indicesData, int numIndices);

		void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	}
}

#endif