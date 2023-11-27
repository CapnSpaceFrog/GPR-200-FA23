#include "GameObject.h"
#include <external/glad.h>

using namespace GizmosLib::OpenGL::GameObject;

GameObject::GameObject(int cornerX, int cornerY, int spriteWidth, int spriteHeight)
{

}

bool GameObject::Draw()
{
	//Need to pass updated UV information to the GPU to draw the correct frame of the sprite
	//This informtaion will all be contained in the Animation, so perhaps we have a Draw function
	//in the Animation class that returns the correct UV information that we use?

	//Does the sprite have its own VBO that we need to bind?
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return false;
}

bool GameObject::SwapActiveAnimation(Animation::AnimationTypes animType)
{
	switch (animType)
	{
		default:
			return false;
			break;
	}
}