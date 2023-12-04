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
			Transform();

			ew::Vec3 Position;
			ew::Vec3 Rotation; //Euler Angles (degrees)
			ew::Vec3 Scale;

			ew::Mat4 GetModelMatrix() const;
		};
	}
}
#endif