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
			struct BatchedSprite
			{
				Sprite* Sprite;
				ew::Mat4 ModelMatrix;
			};

			class SpriteBatcher
			{
			public:
				SpriteBatcher();

				static SpriteBatcher& GetInstance();

				void Add(BatchedSprite& spriteToAdd);

				void DrawBatch();

			private:
				void initialize();

				void clear();

				unsigned int _VAO;
				unsigned int _VBO;
				unsigned int _EBO;

				std::vector<BatchedSprite> _batchedSprites;

				unsigned int _batchTexID;

				Mesh DefaultSpriteMesh;
			};
		}
	}
}

#endif