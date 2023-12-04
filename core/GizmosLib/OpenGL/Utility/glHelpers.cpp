#include "glHelpers.h"
#include <external/stb_image.h>

namespace GizmosLib { namespace OpenGL 
{
	namespace Utility
	{
		int SCREEN_WIDTH = 1080;
		int SCREEN_HEIGHT = 720;

		//Generate and bind a VAO to the current OpenGL context.
		//Takes in an array of vertData and the number of elements in the array.
		unsigned int generateVAO(float* vertData, int numOfVerts, unsigned int* indicesData, int numIndices)
		{
			//VAO
			//Create and assign a new VAO and bind it as active
			unsigned int VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			//Is there ever any reason to touch a VBO after you create it?
			//When working in an abstracted manner, why would someone need to update the data on the VBO?

			//VBO
			//Generate a VBO buffer and pass vertex data to the GPU
			unsigned int VBO;
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (numOfVerts), vertData, GL_STATIC_DRAW);

			//EBO
			//Generate an EBO buffer and pass index data to it
			unsigned int EBO;
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (numIndices), indicesData, GL_STATIC_DRAW);

			//VERTEX ATTRIBUTES
			//Assign Vertex Pos and Color values and set up spacing correctly
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			return VAO;
		}

		//Called when a user resizes the window
		void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			SCREEN_HEIGHT = height;
			SCREEN_WIDTH = width;
		}
	}
} }