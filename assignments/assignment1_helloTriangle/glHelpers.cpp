#include <ew/external/glad.h>

//Generate and bind a VAO to the current OpenGL context.
//Takes in an array of vertData and the number of elements in the array.
unsigned int generateVAO(float* vertData, int numOfVerts)
{
	//VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//VERTEX ATTRIBUTES
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	return VAO;
}
