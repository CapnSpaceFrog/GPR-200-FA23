#ifndef _PROCGEN_
#define _PROCGEN_

#include <ew/mesh.h>

namespace GizmosLib
{
	namespace OpenGL
	{
		namespace Procedural
		{
			ew::MeshData createPlane(float width, float height, int subdivisions);

			ew::MeshData createCylinder(float height, float radius, int segments);

			ew::MeshData createSphere(float radius, int segments);
		}
	}
}
#endif
