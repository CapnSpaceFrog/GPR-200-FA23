#include "spriteBatcher.h"

using namespace GizmosLib::OpenGL::Core;

SpriteBatcher::SpriteBatcher()
{
	if (Instance == nullptr)
	{
		Instance = new SpriteBatcher();
		Instance->initialize();
	}
}

void SpriteBatcher::Add()
{

}

void SpriteBatcher::DrawBatch()
{
	glBindVertexArray(_VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spriteToRender->GetBoundTex());

	glDrawElements(GL_TRIANGLES, _numOfIndices, GL_UNSIGNED_INT, NULL);
}

void SpriteBatcher::initialize()
{
	//Generate a VAO for this Sprite
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	//Generate a VBO for the Sprite
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ew::Vertex), (const void*)offsetof(ew::Vertex, pos));
	glEnableVertexAttribArray(0);

	//Normal attribute
	//Probably won't be using it but just in case I'm leaving it in
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ew::Vertex), (const void*)offsetof(ew::Vertex, normal));
	glEnableVertexAttribArray(1);

	//UV attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ew::Vertex), (const void*)(offsetof(ew::Vertex, uv)));
	glEnableVertexAttribArray(2);
}

void SpriteBatcher::clear()
{

}