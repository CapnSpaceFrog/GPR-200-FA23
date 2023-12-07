#include <external/glad.h>

#include "spriteBatcher.h"
#include <GizmosLib/OpenGL/Core/Sprites/sprite.h>
#include <GizmosLib/OpenGL/Core/Shaders/shaderProgram.h>
#include <ew/mesh.h>

using namespace GizmosLib::OpenGL::Core;

SpriteBatcher::SpriteBatcher()
{
	initialize();
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);

	//Normal attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, UV));
	glEnableVertexAttribArray(1);

	//UV attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, Normal)));
	glEnableVertexAttribArray(2);
}

SpriteBatcher& SpriteBatcher::GetInstance()
{
	static SpriteBatcher _instance;

	return _instance;
}

void SpriteBatcher::Add(Sprite& spriteToAdd)
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	if (spriteToAdd.BoundMesh.Vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * spriteToAdd.BoundMesh.Vertices.size(), spriteToAdd.BoundMesh.Vertices.data(), GL_DYNAMIC_DRAW);

	if (spriteToAdd.BoundMesh.Indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * spriteToAdd.BoundMesh.Indices.size(), spriteToAdd.BoundMesh.Indices.data(), GL_DYNAMIC_DRAW);

	_numOfVerts += spriteToAdd.BoundMesh.Vertices.size();
	_numOfIndices += spriteToAdd.BoundMesh.Indices.size();

	//This is a placeholder solution for knowing which texture this batcher is bound too
	_batchTexID = spriteToAdd.GetBoundTex().TextureID;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//This only supports drawing with one texture type at a time.
void SpriteBatcher::DrawBatch()
{
	glBindVertexArray(_VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _batchTexID);

	glDrawElements(GL_TRIANGLES, _numOfIndices, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);

	clear();
}

void SpriteBatcher::clear()
{
	//Clear all VBO data attached to it
	_batchVertices.clear();
	_batchIndices.clear();

	_numOfVerts = 0;
	_numOfIndices = 0;
}