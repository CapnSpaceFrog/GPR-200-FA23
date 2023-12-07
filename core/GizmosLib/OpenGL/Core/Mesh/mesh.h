#ifndef _MESH_
#define _MESH_

#include <ew/ewMath/ewMath.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
		{
			struct Vertex
			{
				ew::Vec3 Position;
				ew::Vec2 UV;
				ew::Vec3 Normal;
			};

			class Mesh
			{
			public:

				std::vector<Vertex> Vertices;
				std::vector<unsigned int> Indices;

			private:
				
			};
		}
	}
}

#endif 
