#ifndef  _SPRITE_BATCHER_
#define _SPRITE_BATCHER_

#include <vector>
#include <GizmosLib/OpenGL/Core/Sprites/sprite.h>
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

				void Add(Sprite& spriteToAdd);

				void DrawBatch();

			private:
				void initialize();

				void clear();

				unsigned int _VAO;
				unsigned int _VBO;
				unsigned int _EBO;

				std::vector<Vertex> _batchVertices;
				std::vector<unsigned int> _batchIndices;

				int _numOfVerts;
				int _numOfIndices;

				unsigned int _batchTexID;
			};
		}
	}
}

#endif