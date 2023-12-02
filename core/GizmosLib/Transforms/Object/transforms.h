#ifndef _TRANSFORMS_
#define _TRANSFORMS_

#include <ew/ewMath/ewMath.h>

namespace GizmosLib
{
	namespace Transforms
	{
		ew::Mat4 Identity();

		ew::Mat4 Scale(ew::Vec3 s);

		ew::Mat4 RotateX(float rad);

		ew::Mat4 RotateY(float rad);

		ew::Mat4 RotateZ(float rad);

		ew::Mat4 Translate(ew::Vec3 t);

		struct Transform
		{
			ew::Vec3 Position = ew::Vec3(0.0f, 0.0f, 0.0f);
			ew::Vec3 Rotation = ew::Vec3(0.0f, 0.0f, 0.0f); //Euler Angles (degrees)
			ew::Vec3 Scale = ew::Vec3(1.0f, 1.0f, 1.0f);

			ew::Mat4 GetModelMatrix() const;
		};
	}
}
#endif