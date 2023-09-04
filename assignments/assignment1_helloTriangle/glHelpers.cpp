#include <ew/external/glad.h>

//Generate and bind a VAO to the current OpenGL context.
//Takes in an array of vertData and the number of elements in the array.
unsigned int generateVAO(float* vertData, int numOfVerts, unsigned int VBO)
{
	//VAO
	//Create and assign a new VAO and bind it as active
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	//Generate a VBO buffer and pass vertex data to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (numOfVerts), vertData, GL_STATIC_DRAW);

	//VERTEX ATTRIBUTES
	//Assign Vertex Pos and Color values and set up spacing correctly
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return VAO;
}
