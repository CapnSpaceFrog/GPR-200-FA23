#include "GameObject.h"
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include <external/glad.h>

using namespace GizmosLib::OpenGL::Core;

GameObject::GameObject()
{
	Initialize();
}

void GameObject::SetShader(ShaderProgram& shader)
{
	_attachedShader = &shader;
}

void GameObject::SetDefaultSprite(Sprite& sprite)
{
	_defaultSprite = &sprite;
}

void GameObject::SetActiveAnimation(Animation& animation)
{
	_activeAnimation = &animation;
}

bool GameObject::Render()
{
	Sprite* spriteToRender = nullptr;

	if (_defaultSprite == nullptr)
	{
		//TODO: Logging
		return false;
	}

	if (_activeAnimation == nullptr)
	{
		//no bound pointer but we do have a default sprite, so we just render that
		LoadSpriteUV(_defaultSprite->UV);
	}
	else
	{
		//Should really reduce the amount of times we call LoadVertexData
		spriteToRender = _activeAnimation->Play();
		LoadSpriteUV(spriteToRender->UV);
	}

	if (_attachedShader == nullptr)
	{
		//TODO: Logging
		return false;
	}
	else
	{
		_attachedShader->MakeActive();
		_attachedShader->SetUniform1i("uSpriteSheet", 0);
		_attachedShader->SetUniformMatrix("_Model", Transform.GetModelMatrix());
	}

	glBindVertexArray(_VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spriteToRender->GetBoundTex());

	glDrawElements(GL_TRIANGLES, _numOfIndices, GL_UNSIGNED_INT, NULL);

	return true;
}

void GameObject::Initialize()
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

	//PLACEHOLDER
	ew::Vertex bottomLeft;
	bottomLeft.pos = ew::Vec3(-1, -1, 0);
	ew::Vertex bottomRight;
	bottomRight.pos = ew::Vec3(1, -1, 0);
	ew::Vertex topLeft;
	topLeft.pos = ew::Vec3(-1, 1, 0);
	ew::Vertex topRight;
	topRight.pos = ew::Vec3(1, 1, 0);

	vertices = { bottomLeft, bottomRight, topLeft, topRight };
	indices = { 0, 1, 2, 2, 1, 3 };

	if (indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	//Variable Initialization
	_defaultSprite = nullptr;
	Transform = GizmosLib::Transforms::Transform();
	_activeAnimation = nullptr;
}

void GameObject::LoadSpriteUV(const std::vector<ew::Vec2>& uv)
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	//This is the cheeky way of doing this, really we should iterate through each vertex and update the vertex data with that of the current sprite.
	if (uv.size() > 0)
	{
		for (int i = 0; i < uv.size(); i++)
			vertices[i].uv = uv[i];

		glBufferData(GL_ARRAY_BUFFER, sizeof(ew::Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_numOfVerts = vertices.size();
	_numOfIndices = indices.size();
}

GameObject::~GameObject()
{
	_defaultSprite = nullptr;
	_attachedShader = nullptr;
}