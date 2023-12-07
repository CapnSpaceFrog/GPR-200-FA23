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
	Vertex bottomLeft;
	bottomLeft.Position = ew::Vec3(-1, -1, 0);
	bottomLeft.UV = ew::Vec2(sourceXY.x / tex.Width, (sourceXY.y / tex.Height));

	Vertex bottomRight;
	bottomRight.Position = ew::Vec3(1, -1, 0);
	bottomRight.UV = ew::Vec2(((sourceXY.x + pixels) / tex.Width), (sourceXY.y / tex.Height));

	Vertex topLeft;
	topLeft.Position = ew::Vec3(-1, 1, 0);
	topLeft.UV = ew::Vec2((sourceXY.x / tex.Width), ((sourceXY.y + pixels) / tex.Height));

	Vertex topRight;
	topRight.Position = ew::Vec3(1, 1, 0);
	topRight.UV = ew::Vec2(((sourceXY.x + pixels) / tex.Width), ((sourceXY.y + pixels) / tex.Height));

	BoundMesh.Vertices = { bottomLeft, bottomRight, topLeft, topRight };
	BoundMesh.Indices = { 0, 1, 2, 2, 1, 3};
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

	newSprite.sprite = this;
	newSprite.model = transform.GetModelMatrix();

	SpriteBatcher::GetInstance().Add(newSprite);
	return true;
}