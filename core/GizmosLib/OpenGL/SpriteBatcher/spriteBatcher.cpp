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

	//Generate default mesh
	Vertex bottomLeft;
	bottomLeft.Position = ew::Vec3(-1, -1, 0);

	Vertex bottomRight;
	bottomRight.Position = ew::Vec3(1, -1, 0);

	Vertex topLeft;
	topLeft.Position = ew::Vec3(-1, 1, 0);

	Vertex topRight;
	topRight.Position = ew::Vec3(1, 1, 0);

	DefaultSpriteMesh.Vertices = { bottomLeft, bottomRight, topLeft, topRight };
	DefaultSpriteMesh.Indices = { 0, 1, 2, 2, 1, 3 };
}

SpriteBatcher& SpriteBatcher::GetInstance()
{
	static SpriteBatcher _instance;

	return _instance;
}

void SpriteBatcher::Add(BatchedSprite& spriteToAdd)
{
	_batchedSprites.push_back(spriteToAdd);
}

//This only supports drawing with one texture type at a time.
void SpriteBatcher::DrawBatch()
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	//This is a placeholder solution for knowing which texture this batcher is bound too
	_batchTexID = _batchedSprites[0].Sprite->GetBoundTex().TextureID;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < _batchedSprites.size(); i++)
	{
		int uvIndex = 0;

		for (Vertex v : DefaultSpriteMesh.Vertices)
		{
			Vertex newVertex = v;
			ew::Vec4 worldPosV4 = _batchedSprites[i].ModelMatrix * ew::Vec4(newVertex.Position, 1.0f);
			ew::Vec3 worldPosV3 = ew::Vec3(worldPosV4.x, worldPosV4.y, worldPosV4.z);
			newVertex.Position = worldPosV3;
			newVertex.UV = _batchedSprites[i].Sprite->UV[uvIndex];
			vertices.push_back(newVertex);
			uvIndex++;
		}
		
		for (unsigned int index : DefaultSpriteMesh.Indices)
			indices.push_back(index + (DefaultSpriteMesh.Vertices.size() * i));
	}

	if (vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

	if (indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _batchTexID);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	clear();
}

void SpriteBatcher::clear()
{
	_batchedSprites.clear();
}