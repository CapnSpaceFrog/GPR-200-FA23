//This Sprite class is a spin on mesh.h from Eric Winebrenner

#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include "GizmosLib/OpenGL/Core/Shaders/shaderProgram.h"
#include <ew/ewMath/ewMath.h>
#include <ew/mesh.h>

using namespace GizmosLib::OpenGL::Core;

Sprite::Sprite(Texture& tex, ew::Vec2 sourceXY, int pixels)
{
	_tex = &tex;
	_sourceXY = sourceXY;
	_pixels = pixels;

	ew::Vec2 bottomLeft;
	bottomLeft = ew::Vec2(sourceXY.x / tex.Width, (sourceXY.y / tex.Height));

	ew::Vec2 bottomRight;
	bottomRight = ew::Vec2(((sourceXY.x + pixels) / tex.Width), (sourceXY.y / tex.Height));

	ew::Vec2 topLeft;
	topLeft = ew::Vec2((sourceXY.x / tex.Width), ((sourceXY.y + pixels) / tex.Height));

	ew::Vec2 topRight;
	topRight = ew::Vec2(((sourceXY.x + pixels) / tex.Width), ((sourceXY.y + pixels) / tex.Height));

	UV = { bottomLeft, bottomRight, topLeft, topRight };
}

void Sprite::SetBoundTex(Texture& newTex)
{
	_tex = &newTex;
}

Texture* Sprite::GetBoundTex()
{
	return &_tex;
}

bool Sprite::Render(std::vector<Vertex> verts)
{
	//Call SpriteBatcher.Add()
	
}