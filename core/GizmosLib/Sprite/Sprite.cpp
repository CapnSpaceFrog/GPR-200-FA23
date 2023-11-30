//This Sprite class is a spin on mesh.h from Eric Winebrenner

#include "GizmosLib/Sprite/Sprite.h"
#include <external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/mesh.h>

using namespace GizmosLib::OpenGL::Sprite;

void Sprite::Initialize()
{
	if (_initialized)
		return;

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

	_shaderProg = nullptr;

	_initialized = true;
}

Sprite::Sprite()
{
	Initialize();
}

Sprite::Sprite(float cornerX, float cornerY, int texWidth, int texHeight, int pixels)
{
	Initialize();

	//cornerX & cornerY siginify the x,y of the bottom left corner of the UV coordinate for a sprite
	//width & height denote the offset between future sprites
	ew::Vertex bottomLeft;
	bottomLeft.pos = { -1, -1, 0 };
	bottomLeft.uv = ew::Vec2( cornerX / texWidth, ( cornerY / texHeight) );

	ew::Vertex bottomRight;
	bottomRight.pos = { 1, -1, 0 };
	bottomRight.uv = ew::Vec2( ( ( cornerX+pixels ) / texWidth) , ( cornerY / texHeight) );

	ew::Vertex topLeft;
	topLeft.pos = { -1, 1, 0 };
	topLeft.uv = ew::Vec2((cornerX / texWidth), ( ( cornerY+pixels) / texHeight) );

	ew::Vertex topRight;
	topRight.pos = { 1, 1, 0 };
	topRight.uv = ew::Vec2(( (cornerX + pixels) / texWidth), ( ( cornerY+pixels) / texHeight) );

	vertices = {bottomLeft, bottomRight, topLeft, topRight};

	indices = {0, 1, 2, 2, 1, 3};


	LoadVertexData();
}

void Sprite::LoadVertexData()
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

	if (vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, sizeof(ew::Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	if (indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	_numOfVerts = vertices.size();
	_numOfIndices = indices.size();
}

void Sprite::SetBoundTexture(unsigned int texID)
{
	_TEX = texID;
}

void Sprite::SetShader(ew::Shader& shader)
{
	_shaderProg = &shader;
}

void Sprite::Draw(ew::DrawMode mode)
{
	if (!_initialized)
		return;

	glBindVertexArray(_VAO);

	if (_shaderProg == nullptr)
		return;
	else
		_shaderProg->use();

	//Is binding to GL_TEX0 bad or can I assume I'm using this as the active texture slot?
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _TEX);

	_shaderProg->setInt("uSpriteSheet", 0);

	glDrawElements(GL_TRIANGLES, _numOfIndices, GL_UNSIGNED_INT, NULL);
		
}