#include "gameObject.h"
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"

using namespace GizmosLib::Engine::Core;

GameObject::GameObject()
{
	_defaultSprite = nullptr;
	Transform = GizmosLib::Transforms::Transform();
	_activeAnimation = nullptr;
	
}

GameObject::GameObject(Sprite& sprite, Animation& animation, Mesh& mesh)
{
	_defaultSprite = &sprite;
	Transform = GizmosLib::Transforms::Transform();
	_activeAnimation = &animation;
	_mesh = &mesh;
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
		_defaultSprite->Render(*_mesh);
	else
	{
		_activeAnimation->Update();
	}

	return true;
}

GameObject::~GameObject()
{
	_defaultSprite = nullptr;
	_activeAnimation = nullptr;
}