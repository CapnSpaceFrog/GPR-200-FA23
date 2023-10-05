#ifndef _TRANSFORMATIONS_
#define _TRANSFORMATIONS_

#include <ew/ewMath/ewMath.h>

namespace GizmosLib
{
	namespace Math
	{
		namespace Transform
		{
			inline ew::Mat4 Identity()
			{
				return ew::Mat4 (
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
				);
			}

			inline ew::Mat4 Scale(ew::Vec3 s)
			{
				return ew::Mat4 (
					s.x, 0, 0, 0,
					0, s.y, 0, 0,
					0, 0, s.z, 0,
					0, 0, 0, 1
				);
			}

			inline ew::Mat4 RotateX(float rad)
			{
				return ew::Mat4(
					1,		0,				0,					0,
					0,		cos(rad),	-1*sin(rad),	0,
					0,		sin(rad),	cos(rad),		0,
					0,		0,				0,					1
				);
			}

			inline ew::Mat4 RotateY(float rad)
			{
				return ew::Mat4(
					cos(rad),	0,		sin(rad),	0,
					0,				1,		0,				0,
					-sin(rad),	0,		cos(rad),	0,
					0,				0,		0,				1
				);
			}

			inline ew::Mat4 RotateZ(float rad)
			{
				return ew::Mat4(
					cos(rad),	-1*sin(rad),	0,		0,
					sin(rad),	cos(rad),		0,		0,
					0,				0,					1,		0,
					0,				0,					0,		1
				);
			}

			inline ew::Mat4 Translate(ew::Vec3 t)
			{
				return ew::Mat4(
					1, 0, 0, t.x,
					0, 1, 0, t.y,
					0, 0, 1, t.z,
					0, 0, 0, 1
				);
			}

			struct Transform
			{
				ew::Vec3 Position = ew::Vec3(0.0f, 0.0f, 0.0f);
				ew::Vec3 Rotation = ew::Vec3(0.0f, 0.0f, 0.0f); //Euler Angles (degrees)
				ew::Vec3 Scale = ew::Vec3(1.0f, 1.0f, 1.0f);

				ew::Mat4 GetModelMatrix() const
				{
					ew::Mat4 R = RotateZ(Rotation.z * ew::DEG2RAD) * RotateY(Rotation.y * ew::DEG2RAD) * RotateX(Rotation.x * ew::DEG2RAD);
					
					ew::Mat4 T = ew::Mat4(
						1, 0, 0, Position.x,
						0, 1, 0, Position.y,
						0, 0, 1, Position.z,
						0, 0, 0, 1
					);

					ew::Mat4 S = ew::Mat4(
						Scale.x, 0,			0,			0,
						0,			Scale.y, 0,			0,
						0,			0,			Scale.z, 0,
						0,			0,			0,			1
					);

					//Translate * Rotation * Scale
					return T * R * S;
				}
			};

		}
	}
}

#endif