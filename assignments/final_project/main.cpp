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

#include "GizmosLib/OpenGL/glHelpers.h"

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

float prevTime;
ew::Vec3 bgColor = ew::Vec3(0.1f);

struct
{

} AppSettings;

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

	//Global settings
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	//Defult Shader
	ew::Shader defaultUnlit("assets/unLit.vert", "assets/unLit.frag");
	unsigned int spriteSheet = ew::loadTexture("assets/spritesheet.jpg", GL_REPEAT, GL_NEAREST);

	//UNLIT SHADER
	ew::Shader unlitShader("assets/unLit.vert", "assets/unLit.frag");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		//RENDER BACKGROUND
		glClearColor(bgColor.x, bgColor.y,bgColor.z,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultUnlit.use();
		glBindTexture(GL_TEXTURE_2D, spriteSheet);
		defaultUnlit.setInt("_Texture", 0);



		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Animation Settings");

			if (ImGui::CollapsingHeader("Camera"))
			{
				//ImGui::DragFloat3("Target", &camera.target.x, 0.1f);
				//ImGui::Checkbox("Orthographic", &camera.orthographic);
			}

			ImGui::End();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}

	printf("Shutting down...");
}