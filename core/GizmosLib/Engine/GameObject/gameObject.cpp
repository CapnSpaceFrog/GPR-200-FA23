#include <GizmosLib/Engine/GameObject/gameObject.h>
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"

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
		_defaultSprite->Render(_mesh.);
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

GameObject::~GameObject()
{
	_defaultSprite = nullptr;
	_attachedShader = nullptr;
}