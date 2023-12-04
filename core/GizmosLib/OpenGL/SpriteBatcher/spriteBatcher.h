#ifndef  _SPRITE_BATCHER_
#define _SPRITE_BATCHER_

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			class SpriteBatcher
			{
			public:
				static SpriteBatcher* Instance;

				SpriteBatcher();

				void Add();

				void DrawBatch();

				~SpriteBatcher()
				{
					delete Instance;
					Instance = nullptr;
				}

			private:
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