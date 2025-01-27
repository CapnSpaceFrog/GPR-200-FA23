#include <stdio.h>
#include <math.h>

#include <external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/procGen.h>
#include <ew/transform.h>

#include <GizmosLib/OpenGL/glHelpers.h>
#include <GizmosLib/OpenGL/shaderProgram.h>
#include <GizmosLib/Math/camera.h>
#include <GizmosLib/Math/transformations.h>

//Projection will account for aspect ratio!
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const int NUM_CUBES = 4;
ew::Transform cubeTransforms[NUM_CUBES];

int main()
{
	printf("Initializing...");
	if (!glfwInit())
	{
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Camera", NULL, NULL);
	if (window == NULL)
	{
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, GizmosLib::OpenGL::framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress))
	{
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Depth testing - required for depth sorting!
	glEnable(GL_DEPTH_TEST);

	GizmosLib::OpenGL::Shaders::ShaderProgram cubeShader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	
	//Cube mesh
	ew::Mesh cubeMesh(ew::createCube(0.5f));

	//Cube positions
	for (size_t i = 0; i < NUM_CUBES; i++)
	{
		cubeTransforms[i].position.x = i % (NUM_CUBES / 2) - 0.5;
		cubeTransforms[i].position.y = i / (NUM_CUBES / 2) - 0.5;
	}

	GizmosLib::Math::Camera::Camera basicCamera;
	GizmosLib::Math::Camera::CamControls basicCameraControls;
	
	int screenWidth;
	int screenHeight;

	float prevTime = 0;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		GizmosLib::Math::Camera::MoveCamera(window, &basicCamera, &basicCameraControls, deltaTime);
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		//Clear both color buffer AND depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		basicCamera.aspectRatio = ((float)screenWidth / (float)screenHeight);
		
		//Set uniforms
		cubeShader.MakeActive();

		cubeShader.SetUniformMatrix("uView", basicCamera.ViewMatrix());
		cubeShader.SetUniformMatrix("uProjection", basicCamera.ProjectionMatrix());

		for (size_t i = 0; i < NUM_CUBES; i++)
		{
			//Construct model matrix
			cubeShader.SetUniformMatrix("uModel", cubeTransforms[i].getModelMatrix());
			cubeMesh.draw();
		}

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::Text("Cubes");
			for (size_t i = 0; i < NUM_CUBES; i++)
			{
				ImGui::PushID(i);
				if (ImGui::CollapsingHeader("Transform")) {
					ImGui::DragFloat3("Position", &cubeTransforms[i].position.x, 0.05f);
					ImGui::DragFloat3("Rotation", &cubeTransforms[i].rotation.x, 1.0f);
					ImGui::DragFloat3("Scale", &cubeTransforms[i].scale.x, 0.05f);
				}
				ImGui::PopID();
			}

			ImGui::Text("Camera");
			ImGui::DragFloat3("Position", &basicCamera.position.x, 0.05f);
			ImGui::DragFloat3("Look Target", &basicCamera.lookTarget.x, 0.05f);

			ImGui::Checkbox("Orthographic", &basicCamera.orthographic);

			if (basicCamera.orthographic)
			{
				ImGui::DragFloat("Orthographic Height", &basicCamera.orthoHeight, 0.5f);
			}
			else
			{
				ImGui::DragFloat("FoV", &basicCamera.fov, 1.0f);
			}
			
			ImGui::DragFloat("Near Plane", &basicCamera.nearPlane, 1.0f);
			ImGui::DragFloat("Far Plane", &basicCamera.farPlane, 1.0f);

			ImGui::Text("Camera Controller");
			ImGui::Text("Yaw: %f", basicCameraControls.yaw);
			ImGui::Text("Pitch: %f", basicCameraControls.pitch);
			ImGui::DragFloat("Move Speed", &basicCameraControls.moveSpeed, 0.5f);

			if (ImGui::Button("Reset Camera"))
			{
				basicCamera.Reset();
				basicCameraControls.Reset();
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
}

