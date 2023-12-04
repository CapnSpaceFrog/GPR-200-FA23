//This Sprite class is a spin on mesh.h from Eric Winebrenner

#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include "GizmosLib/OpenGL/Core/Shaders/shaderProgram.h"
#include <external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/mesh.h>

using namespace GizmosLib::OpenGL::Core;

Sprite::Sprite(ew::Vec2 spriteSheetCorner, ew::Vec2 texDimensions , int pixels, unsigned int tex)
{
	//cornerX & cornerY siginify the x,y of the bottom left corner of the UV coordinate for a sprite
	//width & height denote the offset between future sprites

	ew::Vec2 bottomLeft;
	bottomLeft = ew::Vec2(spriteSheetCorner.x / texDimensions.x, (spriteSheetCorner.y / texDimensions.y));

	ew::Vec2 bottomRight;
	bottomRight = ew::Vec2(((spriteSheetCorner.x + pixels) / texDimensions.x), (spriteSheetCorner.y / texDimensions.y));

	ew::Vec2 topLeft;
	topLeft = ew::Vec2((spriteSheetCorner.x / texDimensions.x), ((spriteSheetCorner.y + pixels) / texDimensions.y));

	ew::Vec2 topRight;
	topRight = ew::Vec2(((spriteSheetCorner.x + pixels) / texDimensions.x), ((spriteSheetCorner.y + pixels) / texDimensions.y));

	UV = { bottomLeft, bottomRight, topLeft, topRight };

	_TEX = tex;
}

void Sprite::SetBoundTexture(unsigned int texID)
{
	_TEX = texID;
}