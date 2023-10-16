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
					0,		cos(rad),	-sin(rad),	0,
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
					cos(rad),	-sin(rad),	0,		0,
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
					ew::Mat4 R = RotateY(Rotation.y * ew::DEG2RAD) * RotateX(Rotation.x * ew::DEG2RAD) * RotateZ(Rotation.z * ew::DEG2RAD);
					
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

		namespace Camera
		{
			inline ew::Mat4 LookAt(ew::Vec3 cameraPos, ew::Vec3 targetPos, ew::Vec3 upVec)
			{
				ew::Vec3 forward = ew::Normalize(cameraPos - targetPos);
				ew::Vec3 right = ew::Normalize(ew::Cross(upVec, forward));
				ew::Vec3 up = ew::Normalize(ew::Cross(forward, right));

				//A rotation that takes us from no rotation TO the cameras rotation,
				//we want the opposite, so we need to transpose the matrix
				ew::Mat4 rotation = ew::Mat4
				(
					right.x,		right.y,		right.z,		0,
					up.x,			up.y,			up.z,			0,
					forward.x,	forward.y,	forward.z,	0,
					0,				0,				0,				1
				);

				//Translation inverse (since we want to shift our points towards the camera as if the camera was the origin,
				//we simply use the negative of the camera position
				ew::Mat4 translation = Transform::Translate(-cameraPos);

				return rotation * translation;
			}

			//Orthographic Projection
			inline ew::Mat4 Orthographic(float height, float aspect, float nearPlane, float farPlane)
			{
				float width = height * aspect;

				float r = width / 2;
				float t = height / 2;
				float l = -r;
				float b = -t;

				ew::Mat4 orthoProj = ew::Mat4
				(
					2 / (r - l),	0,					0,												-( (r + l) / (r-l) ),
					0,					2 / (t - b),	0,												-( (t + b) / (t - b) ),
					0,					0,					- ( 2 / (farPlane - nearPlane) ),	-( (farPlane + nearPlane) / (farPlane - nearPlane) ),
					0,					0,					0,												1
				);

				return orthoProj;
			}

			//Perspective Projection
			//FOV = vertical aspect ratio (radians)
			inline ew::Mat4 Perspective(float fov, float aspect, float nearPlane, float farPlane)
			{

			}
		}
	}
}
#endif