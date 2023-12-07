#ifndef  _SPRITE_BATCHER_
#define _SPRITE_BATCHER_

#include <vector>
#include <ew/mesh.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class SpriteBatcher
			{
			public:
				SpriteBatcher();

				static SpriteBatcher& GetInstance();

				void Add();

				void DrawBatch();

				~SpriteBatcher();

			private:
				static SpriteBatcher* instance;
				
				void initialize();

				void clear();

				unsigned int _VAO;
				unsigned int _VBO;
				unsigned int _EBO;

				std::vector<ew::Vertex> vertices;
				std::vector<unsigned int> indices;

				int _numOfVerts;
				int _numOfIndices;
			};
		}
	}
}

#endif