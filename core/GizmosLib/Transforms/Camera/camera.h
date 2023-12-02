#ifndef _CAMERA_
#define _CAMERA_

#include <ew/ewMath/ewMath.h>
#include <external/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

namespace GizmosLib
{
	namespace Transforms
	{
		ew::Mat4 LookAt(ew::Vec3 cameraPos, ew::Vec3 targetPos, ew::Vec3 upVec);

		ew::Mat4 Orthographic(float height, float aspect, float nearPlane, float farPlane);

		ew::Mat4 Perspective(float fov, float aspect, float nearPlane, float farPlane);

		struct Camera
		{
			public:
				Camera();

				//World -> View Space Matrix
				ew::Mat4 ViewMatrix();

				//View -> Clip Space Matrix
				ew::Mat4 ProjectionMatrix();

				void Reset();

				ew::Vec3 Position;
				ew::Vec3 LookTarget;

				//Perspective Variables
				float Fov;
				float AspectRatio;
				float NearPlane;
				float FarPlane;

				//Orthographic Variables
				bool IsOrthographic;
				float OrthoHeight;
		};

		struct CameraControls
		{
			public:
				double PrevMouseX, PrevMouseY;
				float Yaw = 0, Pitch = 0; //In Degrees
				float MouseSensitivity = 0.1f;
				bool FirstMouse = true;
				float MoveSpeed = 5.0f;

				void Reset();
		};

		void MoveCamera(GLFWwindow* window, Camera* camera, CameraControls* camControls, float deltaTime);
	}
}
#endif