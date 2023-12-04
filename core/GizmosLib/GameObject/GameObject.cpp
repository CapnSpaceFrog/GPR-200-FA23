#include "GameObject.h"
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include <external/glad.h>

using namespace GizmosLib::OpenGL::Core;

GameObject::GameObject()
{
	_defaultSprite = nullptr;
	Transform = GizmosLib::Transforms::Transform();
	_activeAnimation = nullptr;
}

GameObject::GameObject(Sprite& sprite, Animation& animation)
{
	_defaultSprite = &sprite;
	Transform = GizmosLib::Transforms::Transform();
	_activeAnimation = &animation;
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
	if (_defaultSprite == nullptr)
	{
		//TODO: Logging
		return false;
	}

	if (_activeAnimation == nullptr)
		_defaultSprite->Render();
	else
	{
		_activeAnimation->Update();
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

	return true;
}

void GameObject::Initialize()
{
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