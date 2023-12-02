#ifndef _SPRITE_
#define _SPRITE_

#include "GizmosLib/OpenGL/Core/Shaders/shaderProgram.h"
#include <ew/mesh.h>
#include <vector>

using namespace GizmosLib::OpenGL::Core;

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class Sprite
			{
			public:

				Sprite();

				Sprite(float cornerX, float cornerY, int texWidth, int texHeight, int pixels);

				void SetBoundTexture(unsigned int texID);

				void SetShader(ShaderProgram& shader);

				void Draw();

				unsigned int GetBoundTex() { return _TEX; }

			private:
				void Initialize();

				void LoadVertexData();

				unsigned int _VAO;
				unsigned int _VBO;
				unsigned int _EBO;
				
				unsigned int _TEX;

				bool _initialized = false;

				ShaderProgram* _shaderProg;

				std::vector<ew::Vertex> vertices;
				std::vector<unsigned int> indices;

				int _numOfVerts;
				int _numOfIndices;
			};
		}
	}
}

#endif