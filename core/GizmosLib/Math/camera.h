#ifndef _CAMERA_
#define _CAMERA_

#include <ew/ewMath/ewMath.h>
#include <GizmosLib/Math/transformations.h>
#include <algorithm>

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
					return GizmosLib::Math::Camera::LookAt(position, lookTarget, ew::Vec3(0, 1, 0));
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

				void Reset()
				{
					position = ew::Vec3(0, 0, 5);
					lookTarget = ew::Vec3(0, 0, 0);

					fov = 60;
					nearPlane = 0.1;
					farPlane = 100;

					orthoHeight = 6;

					orthographic = false;
				}
			};

			struct CamControls
			{
				double prevMouseX, prevMouseY;
				float yaw = 0, pitch = 0; //In Degrees
				float mouseSensitivity = 0.1f;
				bool firstMouse = true;
				float moveSpeed = 5.0f;

				void Reset()
				{
					yaw = 0;
					pitch = 0; //In Degrees
					firstMouse = true;
					moveSpeed = 5.0f;
				}
			};

			void MoveCamera(GLFWwindow* window, Camera* camera, CamControls* camControls, float deltaTime)
			{
				//If right mouse is held, lock cursor and allow movement
				if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					camControls->firstMouse = true;
					return;
				}

				//Visibly hide the cursor
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				//Get Screen Input
				double mouseX, mouseY;
				glfwGetCursorPos(window, &mouseX, &mouseY);

				//If we just started clicking prevent camera bug of immediate movement
				if (camControls->firstMouse)
				{
					camControls->firstMouse = false;
					camControls->prevMouseX = mouseX;
					camControls->prevMouseY = mouseY;
				}

				camControls->yaw += (mouseX - camControls->prevMouseX) * camControls->mouseSensitivity;
				
				camControls->pitch -= (mouseY - camControls->prevMouseY) * camControls->mouseSensitivity;

				if (camControls->pitch > 89)
				{
					camControls->pitch = 89;
				}
				else if (camControls->pitch < -89)
				{
					camControls->pitch = -89;
				}

				float yawRad = camControls->yaw * ew::DEG2RAD;
				float pitchRad = camControls->pitch * ew::DEG2RAD;

				ew::Vec3 forward = ew::Vec3(sin(yawRad) * cos(pitchRad), sin(pitchRad), -cos(yawRad) * cos(pitchRad));
				ew::Vec3 right = ew::Normalize(ew::Cross(forward, ew::Vec3(0, 1, 0)));
				ew::Vec3 up = ew::Normalize(ew::Cross(right, forward));

				if (glfwGetKey(window, GLFW_KEY_W))
				{
					camera->position += forward * camControls->moveSpeed * deltaTime;
				}

				if (glfwGetKey(window, GLFW_KEY_S))
				{
					camera->position += -forward * camControls->moveSpeed * deltaTime;
				}

				if (glfwGetKey(window, GLFW_KEY_D))
				{
					camera->position += right * camControls->moveSpeed * deltaTime;
				}

				if (glfwGetKey(window, GLFW_KEY_A))
				{
					camera->position += -right * camControls->moveSpeed * deltaTime;
				}

				if (glfwGetKey(window, GLFW_KEY_Q))
				{
					camera->position += up * camControls->moveSpeed * deltaTime;
				}

				if (glfwGetKey(window, GLFW_KEY_E))
				{
					camera->position += -up * camControls->moveSpeed * deltaTime;
				}

				camera->lookTarget = camera->position + forward;

				camControls->prevMouseX = mouseX;
				camControls->prevMouseY = mouseY;
			}
		}
	}
}
#endif