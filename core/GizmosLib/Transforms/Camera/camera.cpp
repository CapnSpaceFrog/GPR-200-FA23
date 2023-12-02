#include <ew/ewMath/ewMath.h>
#include <GizmosLib/Transforms/Object/transforms.h>
#include "camera.h"

namespace GizmosLib
{
	namespace Transforms
	{
		ew::Mat4 LookAt(ew::Vec3 cameraPos, ew::Vec3 targetPos, ew::Vec3 upVec)
		{
			ew::Vec3 forward = ew::Normalize(cameraPos - targetPos);
			ew::Vec3 right = ew::Normalize(ew::Cross(upVec, forward));
			ew::Vec3 up = ew::Normalize(ew::Cross(forward, right));

			//A rotation that takes us from no rotation TO the cameras rotation,
			//we want the opposite, so we need to transpose the matrix
			ew::Mat4 rotation = ew::Mat4
			(
				right.x, right.y, right.z, 0,
				up.x, up.y, up.z, 0,
				forward.x, forward.y, forward.z, 0,
				0, 0, 0, 1
			);

			//Translation inverse (since we want to shift our points towards the camera as if the camera was the origin,
			//we simply use the negative of the camera position
			ew::Mat4 translation = Translate(-cameraPos);

			return rotation * translation;
		}

		//Orthographic Projection
		ew::Mat4 Orthographic(float height, float aspect, float nearPlane, float farPlane)
		{
			float width = height * aspect;

			float r = width / 2;
			float t = height / 2;
			float l = -r;
			float b = -t;

			ew::Mat4 orthoProj = ew::Mat4
			(
				2 / (r - l), 0, 0, -((r + l) / (r - l)),
				0, 2 / (t - b), 0, -((t + b) / (t - b)),
				0, 0, -(2 / (farPlane - nearPlane)), -((farPlane + nearPlane) / (farPlane - nearPlane)),
				0, 0, 0, 1
			);

			return orthoProj;
		}

		//Perspective Projection
		//FOV = vertical aspect ratio (radians)
		ew::Mat4 Perspective(float fov, float aspect, float nearPlane, float farPlane)
		{
			fov *= ew::DEG2RAD;

			float e00 = 1 / (tan(fov / 2) * aspect);
			float e11 = 1 / (tan(fov / 2));
			float e22 = (nearPlane + farPlane) / (nearPlane - farPlane);
			float e32 = (2 * farPlane * nearPlane) / (nearPlane - farPlane);

			ew::Mat4 perspectiveProj = ew::Mat4
			(
				e00, 0.0f, 0.0f, 0.0f,
				0.0f, e11, 0.0f, 0.0f,
				0.0f, 0.0f, e22, e32,
				0.0f, 0.0f, -1.0f, 0.0f
			);

			return perspectiveProj;
		}

		Camera::Camera()
		{
			Position = ew::Vec3(0, 0, 5);

			Fov = 60;
			AspectRatio = 0;
			NearPlane = 0.1;
			FarPlane = 100;

			OrthoHeight = 6;

			IsOrthographic = false;
		}

		ew::Mat4 Camera::ViewMatrix()
		{
			return LookAt(Position, LookTarget, ew::Vec3(0, 1, 0));
		}

		ew::Mat4 Camera::ProjectionMatrix()
		{
			ew::Mat4 proj;

			if (IsOrthographic)
			{
				proj = Orthographic(OrthoHeight, AspectRatio, NearPlane, FarPlane);
			}
			else
			{
				proj = Perspective(Fov, AspectRatio, NearPlane, FarPlane);
			}

			return proj;
		}

		void Camera::Reset()
		{
			Position = ew::Vec3(0, 0, 5);
			LookTarget = ew::Vec3(0, 0, 0);

			Fov = 60;
			NearPlane = 0.1;
			FarPlane = 100;

			OrthoHeight = 6;

			IsOrthographic = false;
		}

		void CameraControls::Reset()
		{
			Yaw = 0;
			Pitch = 0; //In Degrees
			FirstMouse = true;
			MoveSpeed = 5.0f;
		}

		void MoveCamera(GLFWwindow* window, Camera* camera, CameraControls* camControls, float deltaTime)
		{
			//If right mouse is held, lock cursor and allow movement
			if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2))
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				camControls->FirstMouse = true;
				return;
			}

			//Visibly hide the cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			//Get Screen Input
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			//If we just started clicking prevent camera bug of immediate movement
			if (camControls->FirstMouse)
			{
				camControls->FirstMouse = false;
				camControls->PrevMouseX = mouseX;
				camControls->PrevMouseY = mouseY;
			}

			camControls->Yaw += (mouseX - camControls->PrevMouseX) * camControls->MouseSensitivity;

			camControls->Pitch -= (mouseY - camControls->PrevMouseY) * camControls->MouseSensitivity;

			if (camControls->Pitch > 89)
			{
				camControls->Pitch = 89;
			}
			else if (camControls->Pitch < -89)
			{
				camControls->Pitch = -89;
			}

			float yawRad = camControls->Yaw * ew::DEG2RAD;
			float pitchRad = camControls->Pitch * ew::DEG2RAD;

			ew::Vec3 forward = ew::Vec3(sin(yawRad) * cos(pitchRad), sin(pitchRad), -cos(yawRad) * cos(pitchRad));
			ew::Vec3 right = ew::Normalize(ew::Cross(forward, ew::Vec3(0, 1, 0)));
			ew::Vec3 up = ew::Normalize(ew::Cross(right, forward));

			if (glfwGetKey(window, GLFW_KEY_W))
			{
				camera->Position += forward * camControls->MoveSpeed * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_S))
			{
				camera->Position += -forward * camControls->MoveSpeed * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_D))
			{
				camera->Position += right * camControls->MoveSpeed * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_A))
			{
				camera->Position += -right * camControls->MoveSpeed * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_Q))
			{
				camera->Position += up * camControls->MoveSpeed * deltaTime;
			}

			if (glfwGetKey(window, GLFW_KEY_E))
			{
				camera->Position += -up * camControls->MoveSpeed * deltaTime;
			}

			camera->LookTarget = camera->Position + forward;

			camControls->PrevMouseX = mouseX;
			camControls->PrevMouseY = mouseY;
		}
	}
}