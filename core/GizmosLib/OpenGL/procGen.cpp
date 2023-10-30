#include <GizmosLib/OpenGL/procGen.h>
#include <ew/mesh.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Procedural
		{
			ew::MeshData createPlane(float width, float height, int subdivisions)
			{
				ew::MeshData newPlane;
				ew::Vertex vert;

				//Verticies
				for (int row = 0; row <= subdivisions; row++)
				{
					for (int col = 0; col <= subdivisions; col++)
					{
						vert.pos.x = width * ( (float)col / subdivisions);
						vert.pos.z = -height * ( (float)row / subdivisions);

						vert.normal = ew::Vec3(0.0f, 1.0f, 0.0f);

						vert.uv = ew::Vec2((float)col / subdivisions , (float)row / subdivisions );

						newPlane.vertices.push_back(vert);
					}
				}

				//Indicies
				//Always have 1 more column than subdivisions
				int columns = subdivisions + 1;

				for (int row = 0; row < subdivisions; row++)
				{
					for (int col = 0; col < subdivisions; col++)
					{
						int start = row * columns + col;

						newPlane.indices.push_back(start);
						newPlane.indices.push_back(start + 1);
						newPlane.indices.push_back(start + columns + 1);
					}
				}

				return newPlane;
			}

			ew::MeshData createCylinder(float height, float radius, int segments)
			{
				ew::MeshData newCylinder;

				return newCylinder;
			}

			ew::MeshData createSphere(float radius, int segments)
			{
				ew::MeshData newSphere;

				return newSphere;
			}
		}
	}
}