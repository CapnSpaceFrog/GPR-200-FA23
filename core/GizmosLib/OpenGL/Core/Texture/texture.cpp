#include <external/stb_image.h>
#include <external/glad.h>
#include "texture.h"

using namespace GizmosLib::OpenGL::Core;

Texture::Texture(const char* filePath, GLenum minFilterMode, GLenum magFilterMode, GLenum wrapMode)
{
	loadTexture(filePath, minFilterMode, magFilterMode, wrapMode);
}

void Texture::UpdateTexPath(const char* filePath)
{
	loadTexture(filePath, _minFilterMode, _magFilterMode, _wrapMode);
}

void Texture::ChangeWrapMode(GLenum wrapMode)
{
	_wrapMode = wrapMode;

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::ChangeMinFilter(GLenum minFilter)
{
	_minFilterMode = minFilter;

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::ChangeMagFilter(GLenum magFilter)
{
	_magFilterMode = magFilter;

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::loadTexture(const char* filePath, GLenum minFilterMode, GLenum magFilterMode, GLenum wrapMode)
{
	stbi_set_flip_vertically_on_load(true);
	
	_wrapMode = wrapMode;
	_minFilterMode = minFilterMode;
	_magFilterMode = magFilterMode;

	int numComponents;
	unsigned char* imgData = stbi_load(filePath, &Width, &Height, &numComponents, 0);

	if (imgData == NULL)
	{
		printf("Failed to load image %s", filePath);
		stbi_image_free(imgData);
		return false;
	}

	GLenum internalFormat;
	switch (numComponents)
	{
	case 1:
		internalFormat = GL_RED;
		break;

	case 2:
		internalFormat = GL_RG;
		break;

	case 3:
		internalFormat = GL_RGB;
		break;

	case 4:
		internalFormat = GL_RGBA;
		break;

	default:
		printf("Did not get a proper internal format when loading texture.");
		return false;
	}

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, Width, Height, 0, internalFormat, GL_UNSIGNED_BYTE, imgData);

	//Set the texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	//Set the texture filtering (GL_TEXTURE_MIN must be set for proper functionality)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);

	//Generate MIPMAPS for the texture
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(imgData);

	return true;
}