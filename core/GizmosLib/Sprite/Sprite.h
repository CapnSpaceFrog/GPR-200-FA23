#ifndef _SPRITE_
#define _SPRITE_

#include <ew/mesh.h>
#include <ew/shader.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Sprite
		{
			class Sprite
			{
			public:

				Sprite();

				Sprite(float cornerX, float cornerY, int texWidth, int texHeight, int pixels);

				void SetBoundTexture(unsigned int texID);

				void SetShader(ew::Shader &shader);

				void Draw(ew::DrawMode mode);

				unsigned int GetBoundTex() { return _TEX; }

			private:
				void Initialize();

				void LoadVertexData();

				unsigned int _VAO;
				unsigned int _VBO;
				unsigned int _EBO;
				
				unsigned int _TEX;

				bool _initialized = false;

				ew::Shader* _shaderProg;

				std::vector<ew::Vertex> vertices;
				std::vector<unsigned int> indices;

				int _numOfVerts;
				int _numOfIndices;
			};
		}
	}
}

#endif