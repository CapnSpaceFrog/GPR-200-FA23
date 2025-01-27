#include <stdio.h>
#include <math.h>

#include <external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/shader.h>
#include <ew/texture.h>
#include <ew/procGen.h>
#include <ew/transform.h>
#include <ew/camera.h>
#include <ew/cameraController.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void resetCamera(ew::Camera& camera, ew::CameraController& cameraController);

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

const int MAX_LIGHTS = 4;

float prevTime;
ew::Vec3 bgColor = ew::Vec3(0.1f);

ew::Camera camera;
ew::CameraController cameraController;

struct Light
{
	ew::Vec3 Position = ew::Vec3(0, 0, 0);
	ew::Vec3 Color = ew::Vec3(1, 1, 1);
	ew::Transform Transform;
};

Light lights[4];

struct
{
	int NumOfLights = 1;
	bool OrbitLights = true;
	float OrbitRadius = 2.0f;
	bool BlinnPhong = false;

	ew::Vec3 AmbientLightColor = ew::Vec3(1, 1, 1);
	float Ambient = 0;
	float Diffuse = 0;
	float Specular = 0;
	float Shininess = 2;

} AppSettings;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Camera", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//Global settings
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	//LIT SHADER
	ew::Shader shader("assets/defaultLit.vert", "assets/defaultLit.frag");
	unsigned int brickTexture = ew::loadTexture("assets/brick_color.jpg",GL_REPEAT,GL_LINEAR);

	//UNLIT SHADER
	ew::Shader unlitShader("assets/unLit.vert", "assets/unLit.frag");

	//Create cube
	ew::Mesh cubeMesh(ew::createCube(1.0f));
	ew::Mesh planeMesh(ew::createPlane(5.0f, 5.0f, 10));
	ew::Mesh sphereMesh(ew::createSphere(0.5f, 64));
	ew::Mesh cylinderMesh(ew::createCylinder(0.5f, 1.0f, 32));

	//Initialize transforms
	ew::Transform cubeTransform;
	ew::Transform planeTransform;
	ew::Transform sphereTransform;
	ew::Transform cylinderTransform;
	planeTransform.position = ew::Vec3(0, -1.0, 0);
	sphereTransform.position = ew::Vec3(-1.5f, 0.0f, 0.0f);
	cylinderTransform.position = ew::Vec3(1.5f, 0.0f, 0.0f);

	ew::Mesh lightMeshes[MAX_LIGHTS] = { ew::Mesh(ew::createSphere(1.0f, 8)), ew::Mesh(ew::createSphere(1.0f, 8)), ew::Mesh(ew::createSphere(1.0f, 8)), ew::Mesh(ew::createSphere(1.0f, 8)) };

	resetCamera(camera,cameraController);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		//Update camera
		camera.aspectRatio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
		cameraController.Move(window, &camera, deltaTime);

		//RENDER
		glClearColor(bgColor.x, bgColor.y,bgColor.z,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glBindTexture(GL_TEXTURE_2D, brickTexture);
		shader.setInt("_Texture", 0);
		shader.setMat4("_ViewProjection", camera.ProjectionMatrix() * camera.ViewMatrix());

		//Draw shapes
		shader.setMat4("_Model", cubeTransform.getModelMatrix());
		cubeMesh.draw();

		shader.setMat4("_Model", planeTransform.getModelMatrix());
		planeMesh.draw();

		shader.setMat4("_Model", sphereTransform.getModelMatrix());
		sphereMesh.draw();

		shader.setMat4("_Model", cylinderTransform.getModelMatrix());
		cylinderMesh.draw();

		//Update our light properties
		for (int i = 0; i < AppSettings.NumOfLights; i++)
		{
			shader.setVec3("_Lights[" + std::to_string(i) + "].pos", lights[i].Transform.position);
			shader.setVec3("_Lights[" + std::to_string(i) + "].color", lights[i].Color);
		}

		shader.setVec3("uAmbientLightColor", AppSettings.AmbientLightColor);
		shader.setVec3("uCameraPos", camera.position);

		shader.setFloat("uAmbient", AppSettings.Ambient);
		shader.setFloat("uDiffuse", AppSettings.Diffuse);
		shader.setFloat("uSpecular", AppSettings.Specular);
		shader.setFloat("uShininess", AppSettings.Shininess);

		shader.setInt("uActiveLights", AppSettings.NumOfLights);

		shader.setInt("uBlinnPhongSpec", AppSettings.BlinnPhong);

		//Render point lights
		//Draw the lights and set their default unlit color
		unlitShader.use();
		unlitShader.setMat4("_ViewProjection", camera.ProjectionMatrix() * camera.ViewMatrix());

		for (int i = 0; i < AppSettings.NumOfLights; i++)
		{
			lights[i].Transform.scale = 0.5f;

			//Draw the light
			if (AppSettings.OrbitLights)
			{
				lights[i].Transform.position = ew::Vec3(cos(i * (2 * ew::PI / 4) + time) * AppSettings.OrbitRadius, 2, -sin(i * (2 * ew::PI / 4) + time) * AppSettings.OrbitRadius);
			}
			else
			{
				lights[i].Transform.position = lights->Position;
			}

			unlitShader.setMat4("_Model", lights[i].Transform.getModelMatrix());
			unlitShader.setVec3("_Color", lights[i].Color);
			lightMeshes[i].draw();
		}

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			if (ImGui::CollapsingHeader("Camera")) {
				ImGui::DragFloat3("Position", &camera.position.x, 0.1f);
				ImGui::DragFloat3("Target", &camera.target.x, 0.1f);
				ImGui::Checkbox("Orthographic", &camera.orthographic);
				if (camera.orthographic) {
					ImGui::DragFloat("Ortho Height", &camera.orthoHeight, 0.1f);
				}
				else {
					ImGui::SliderFloat("FOV", &camera.fov, 0.0f, 180.0f);
				}
				ImGui::DragFloat("Near Plane", &camera.nearPlane, 0.1f, 0.0f);
				ImGui::DragFloat("Far Plane", &camera.farPlane, 0.1f, 0.0f);
				ImGui::DragFloat("Move Speed", &cameraController.moveSpeed, 0.1f);
				ImGui::DragFloat("Sprint Speed", &cameraController.sprintMoveSpeed, 0.1f);
				if (ImGui::Button("Reset")) {
					resetCamera(camera, cameraController);
				}
			}

			ImGui::ColorEdit3("BG color", &bgColor.x);

			ImGui::DragInt("Num Lights", &AppSettings.NumOfLights, 1.0f, 0.0f, MAX_LIGHTS);

			ImGui::Checkbox("Orbit Lights", &AppSettings.OrbitLights);
			ImGui::DragFloat("Orbit Radius", &AppSettings.OrbitRadius, 0.05f, 0.5f);

			ImGui::Checkbox("Blinn-Phong", &AppSettings.BlinnPhong);

			for (int i = 0; i < AppSettings.NumOfLights; i++)
			{
				ImGui::PushID(i);

				if (ImGui::CollapsingHeader("Light"))
				{
					if (AppSettings.OrbitLights)
					{
						//Display the position values of the lights
						ImGui::Text("%f, %f, %f", lights[i].Position.x, lights[i].Position.y, lights[i].Position.z);
					}
					else
					{
						//Allow for editable light settings
						ImGui::DragFloat3("Position", &lights[i].Position.x, 0.1f);
					}
					
					ImGui::ColorEdit3("Color", &lights[i].Color.x, 0.1f);
				}

				ImGui::PopID();
			}

			if (ImGui::CollapsingHeader("Material"))
			{
				ImGui::ColorEdit3("Ambient Color", &AppSettings.AmbientLightColor.x);
				ImGui::DragFloat("AmbientK", &AppSettings.Ambient, 0.05f, 0.0f, 1.0f);
				ImGui::DragFloat("DiffuseK", &AppSettings.Diffuse, 0.05f, 0.0f, 1.0f);
				ImGui::DragFloat("SpecularK", &AppSettings.Specular, 0.05f, 0.0f, 1.0f);
				ImGui::DragFloat("Shininess", &AppSettings.Shininess, 0.1f, 2.0f, 256.0f);
			}

			ImGui::End();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void resetCamera(ew::Camera& camera, ew::CameraController& cameraController) {
	camera.position = ew::Vec3(0, 0, 5);
	camera.target = ew::Vec3(0);
	camera.fov = 60.0f;
	camera.orthoHeight = 6.0f;
	camera.nearPlane = 0.1f;
	camera.farPlane = 100.0f;
	camera.orthographic = false;

	cameraController.yaw = 0.0f;
	cameraController.pitch = 0.0f;
}


