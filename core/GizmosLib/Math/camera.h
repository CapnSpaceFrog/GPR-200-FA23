#ifndef _CAMERA_
#define _CAMERA_

#include <ew/ewMath/ewMath.h>
#include <GizmosLib/Math/transformations.h>

using namespace GizmosLib::Math::Transform;

namespace GizmosLib
{
	namespace Math
	{
		namespace Camera
		{
			struct Camera
			{
				Camera()
				{
					position = ew::Vec3(0, 0, 5);

					fov = 60;
					aspectRatio = 0;
					nearPlane = 0.1;
					farPlane = 100;

					orthoHeight = 6;

					orthographic = false;
				}

				ew::Vec3 position;
				ew::Vec3 lookTarget;

				float fov;
				float aspectRatio;
				float nearPlane;
				float farPlane;
				
				bool orthographic;

				float orthoHeight;

				//World -> View Space Matrix
				ew::Mat4 ViewMatrix()
				{
					return LookAt(position, lookTarget, ew::Vec3(0, 1, 0));
				}

				//View -> Clip Space Matrix
				ew::Mat4 ProjectionMatrix()
				{
					ew::Mat4 proj;

					if (orthographic)
					{
						proj = Orthographic(orthoHeight, aspectRatio, nearPlane, farPlane);
					}
					else
					{
						proj = Perspective(fov, aspectRatio, nearPlane, farPlane);
					}

					return proj;
				}
			};
		}
	}
}
#endif