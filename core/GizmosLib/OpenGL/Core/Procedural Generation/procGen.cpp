#include <GizmosLib/OpenGL/Core/Procedural Generation/procGen.h>
#include <ew/mesh.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Core
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

						//Bottom Right Triangle
						newPlane.indices.push_back(start);
						newPlane.indices.push_back(start + 1);
						newPlane.indices.push_back(start + columns + 1);

						//Top Left Triangle
						newPlane.indices.push_back(start);
						newPlane.indices.push_back(start+columns+1);
						newPlane.indices.push_back(start+columns);
					}
				}

				return newPlane;
			}

			ew::MeshData createCylinder(float height, float radius, int segments)
			{
				ew::MeshData newCylinder;
				ew::Vertex vert;

				// y = 0 is center of cylinder in local space
				float topY = height / 2.0f;
				float bottomY = -topY;

				//VERTICES
				//Top Center Vertex
				vert.pos = { 0, topY, 0 };
				vert.normal = { 0, 1, 0 };
				vert.uv = {0.5, 0.5};
				newCylinder.vertices.push_back(vert);

				//Top Ring Vertices (top face)
				float thetaStep = 2 * ew::PI / segments;

				for (int i = 0; i <= segments; i++)
				{
					float theta = i * thetaStep;
					
					vert.pos.x = cos(theta) * radius;
					vert.pos.z = sin(theta) * radius;
					vert.pos.y = topY;

					vert.normal = { 0, 1, 0 };

					vert.uv = ew::Vec2( (cos(theta) + 1) * 0.5f, (sin(theta) + 1) * 0.5f );

					newCylinder.vertices.push_back(vert);
				}

				//Top Ring Vertices (side face)
				for (int i = 0; i <= segments; i++)
				{
					float theta = i * thetaStep;

					vert.pos.x = cos(theta) * radius;
					vert.pos.z = sin(theta) * radius;
					vert.pos.y = topY;

					vert.normal = ew::Normalize( vert.pos - ew::Vec3(0, topY, 0) );

					vert.uv = { (i / (float)segments), 1 };

					newCylinder.vertices.push_back(vert);
				}

				//Bottom Ring Vertices (side face)
				for (int i = 0; i <= segments; i++)
				{
					float theta = i * thetaStep;

					vert.pos.x = cos(theta) * radius;
					vert.pos.z = sin(theta) * radius;
					vert.pos.y = bottomY;

					vert.normal = ew::Normalize(vert.pos - ew::Vec3(0, bottomY, 0));

					vert.uv = { ( i / (float)segments ), 0 };

					newCylinder.vertices.push_back(vert);
				}

				//Bottom Ring Vertices (bottom face)
				for (int i = 0; i <= segments; i++)
				{
					float theta = i * thetaStep;

					vert.pos.x = cos(theta) * radius;
					vert.pos.z = sin(theta) * radius;
					vert.pos.y = bottomY;

					vert.normal = { 0, -1, 0 };

					vert.uv = ew::Vec2( (cos(theta) + 1) * 0.5f , (sin(theta) + 1) * 0.5f );

					newCylinder.vertices.push_back(vert);
				}

				//Bottom Center Vertex
				vert.pos = { 0, bottomY, 0 };
				vert.normal = { 0, -1, 0 };
				vert.uv = { 0.5f, 0.5f };
				newCylinder.vertices.push_back(vert);

				//INDICES

				//TOP CAP
				int start = 1;
				int center = 0;

				for (int i = 0; i < segments; i++)
				{
					newCylinder.indices.push_back(start + i);
					newCylinder.indices.push_back(center);
					newCylinder.indices.push_back(start + i + 1);
				}

				//BOTTOM CAP
				start = 1 + ( (segments+1)*3 );
				center = 1 + ( (segments+1)*4 );

				for (int i = 0; i < segments; i++)
				{
					newCylinder.indices.push_back(start + i + 1);
					newCylinder.indices.push_back(center);
					newCylinder.indices.push_back(start + i);
				}

				//SIDES
				int sideStart = 1 + segments + 1;
				int columns = segments + 1;

				for (int i = 0; i < columns; i++)
				{
					start = sideStart + i;

					//Top Right Corner Triangle
					newCylinder.indices.push_back(start);
					newCylinder.indices.push_back(start+1);
					newCylinder.indices.push_back(start + columns);

					//Bottom Left Corner 
					newCylinder.indices.push_back(start + 1);
					newCylinder.indices.push_back(start + columns + 1);
					newCylinder.indices.push_back(start + columns);
				}

				return newCylinder;
			}

			ew::MeshData createSphere(float radius, int segments)
			{
				ew::MeshData newSphere;
				ew::Vertex vert;

				//VERTEX
				float yawStep = 2 * ew::PI / segments;
				float pitchStep = ew::PI / segments;

				int columns = segments + 1;

				for (int row = 0; row <= segments; row++)
				{
					//First and last row converge at the poles

					float pitch = row * pitchStep;

					for (int col = 0; col <= segments; col++)
					{
						float yaw = col * yawStep;

						vert.pos.x = radius * cos(yaw) * sin(pitch);
						vert.pos.y = radius * cos(pitch);
						vert.pos.z = radius * sin(yaw) * sin(pitch);

						vert.normal = ew::Normalize(vert.pos);

						vert.uv = ew::Vec2((float)col / columns, ( ( (float)row / columns ) - 1.0f) * -1 );

						newSphere.vertices.push_back(vert);
					}
				}

				//INDICIES
				//Top Cap 
				int poleStart = 0;
				int sideStart = segments + 1;

				for (int i = 0; i < segments; i++)
				{
					newSphere.indices.push_back(sideStart + i);
					newSphere.indices.push_back(poleStart + i); //This is the pole vertex
					newSphere.indices.push_back(sideStart + i + 1);
				}

				//Sides

				//Need to skip the top & bottom rows, since we already wound those
				for (int row = 1; row < (segments - 1); row++)
				{
					for (int col = 0; col < segments; col++)
					{
						int start = row * columns + col;

						//Top Right Triangles
						newSphere.indices.push_back(start);
						newSphere.indices.push_back(start + 1);
						newSphere.indices.push_back(start + columns);

						//Bottom Right Triangles
						newSphere.indices.push_back(start + 1);
						newSphere.indices.push_back(start + columns + 1);
						newSphere.indices.push_back(start + columns);
					}
				}

				//Bottom Cap
				poleStart = ((segments+1)*(columns-1));
				sideStart = ((segments + 1) * (columns-2) );

				for (int i = 0; i < segments; i++)
				{
					newSphere.indices.push_back(sideStart + i + 1);

					newSphere.indices.push_back(poleStart + i); //This is the pole vertex
					
					newSphere.indices.push_back(sideStart + i);
				}

				return newSphere;
			}
		}
	}
}