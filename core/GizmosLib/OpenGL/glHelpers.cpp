#include "glHelpers.h"
#include <external/stb_image.h>

namespace GizmosLib { namespace OpenGL 
{
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
	}

	unsigned int loadTexture(const char* filePath)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, numComponents;
		unsigned char* imgData = stbi_load(filePath, &width, &height, &numComponents, 0);
		
		if (imgData == NULL)
		{
			printf("Failed to load image %s", filePath);
			stbi_image_free(imgData);
			return 0;
		}

		GLenum internalFormat;
		switch (numComponents)
		{
		case 1:
			internalFormat = GL_RED;
			break;

		case 2:
			internalFormat = GL_RG;
			break;

		case 3:
			internalFormat = GL_RGB;
			break;

		case 4:
			internalFormat = GL_RGBA;
			break;

		default:
			printf("Did not get a proper internal format when loading texture.");
			return 0;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
	}
} }