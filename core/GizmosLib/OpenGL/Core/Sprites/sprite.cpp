//This Sprite class is a spin on mesh.h from Eric Winebrenner

#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include <GizmosLib/OpenGL/SpriteBatcher/spriteBatcher.h>
#include <GizmosLib/Transforms/Object/transforms.h>
#include <ew/ewMath/ewMath.h>

using namespace GizmosLib::OpenGL::Core;
using namespace GizmosLib::Transforms;

Sprite::Sprite(Texture& tex, ew::Vec2 sourceXY, int pixels)
	: _tex(&tex), _sourceXY(sourceXY), _pixels(pixels)
{
	ew::Vec2 bottomLeft = ew::Vec2(sourceXY.x / tex.Width, (sourceXY.y / tex.Height));
	
	ew::Vec2 bottomRight = ew::Vec2(((sourceXY.x + pixels) / tex.Width), (sourceXY.y / tex.Height));
	
	ew::Vec2 topLeft = ew::Vec2((sourceXY.x / tex.Width), ((sourceXY.y + pixels) / tex.Height));
	
	ew::Vec2 topRight = ew::Vec2(((sourceXY.x + pixels) / tex.Width), ((sourceXY.y + pixels) / tex.Height));

	UV = { bottomLeft, bottomRight, topLeft, topRight };
}

void Sprite::SetBoundTex(Texture& newTex)
{
	_tex = &newTex;
}

Texture& Sprite::GetBoundTex()
{
	return *_tex;
}

bool Sprite::Render(Transform& transform)
{
	//Package together the mesh data with the SpriteData,
	//and then send the SpriteData to the SpriteBatcher

	BatchedSprite newSprite;

	newSprite.Sprite = this;
	newSprite.ModelMatrix = transform.GetModelMatrix();

	SpriteBatcher::GetInstance().Add(newSprite);
	return true;
}