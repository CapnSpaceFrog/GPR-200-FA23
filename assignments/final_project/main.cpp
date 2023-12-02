#include <stdio.h>
#include <math.h>
#include <string>

#include <external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GizmosLib/OpenGL/Utility/glHelpers.h"
#include "GizmosLib/OpenGL/Core/Shaders/shaderProgram.h"
#include "GizmosLib/OpenGL/Core/Sprites/sprite.h"
#include "GizmosLib/Transforms/Object/transforms.h"
#include "GizmosLib/Transforms/Camera/camera.h"

using namespace GizmosLib::Transforms;
using namespace GizmosLib::OpenGL::Core;
using namespace GizmosLib::OpenGL::Utility;

float prevTime;
ew::Vec3 bgColor = ew::Vec3(0.1f);

struct
{
	float OrthoHeight = 1;
	float NearPlane = 0.1f;
	float FarPlane = 10.0f;
} AppSettings;

int main()
{
	printf("Initializing...");

	if (!glfwInit())
	{
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(GizmosLib::OpenGL::Utility::SCREEN_WIDTH, GizmosLib::OpenGL::Utility::SCREEN_HEIGHT, "Camera", NULL, NULL);
	
	if (window == NULL)
	{
		printf("GLFW failed to create window");
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Defult Shader
	ShaderProgram defaultUnlit("assets/unLit.vert", "assets/unLit.frag");

	unsigned int MedievalSpriteSheet = GizmosLib::OpenGL::Utility::loadTexture("assets/Sprite Sheets/MedievalTownfolkSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 medievalSpriteSize = { 0, 0};
	unsigned int ElementalSpriteSheet = GizmosLib::OpenGL::Utility::loadTexture("assets/Sprite Sheets/ElementalWarriorsSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 elementalSpriteSize = { 0, 0 };
	unsigned int SteampunkSpriteSheet = GizmosLib::OpenGL::Utility::loadTexture("assets/Sprite Sheets/SteampunkCharacterSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 steampunkSpriteSize = { 0, 0 };


	Sprite testSprite = Sprite(0, 0, 128, 128, 32);

	testSprite.SetBoundTexture(ElementalSpriteSheet);

	testSprite.SetShader(defaultUnlit);
	
	//SPRITE SETUP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		//RENDER BACKGROUND
		glClearColor(bgColor.x, bgColor.y,bgColor.z,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultUnlit.MakeActive();

		defaultUnlit.SetUniformMatrix("_OrthoProjection", Orthographic(AppSettings.OrthoHeight,
			((float)GizmosLib::OpenGL::Utility::SCREEN_WIDTH / (float)GizmosLib::OpenGL::Utility::SCREEN_HEIGHT),
			AppSettings.NearPlane,
			AppSettings.FarPlane));

		//defaultUnlit.SetUniformMatrix("_Model", testSprite.GetModelMatrix());
		defaultUnlit.SetUniformMatrix("_View", LookAt(ew::Vec3(0, 0, 5), ew::Vec3(0, 0, 0), ew::Vec3(0, 1, 0)));

		testSprite.Draw();

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");

			if (ImGui::CollapsingHeader("Camera"))
			{
				ImGui::DragFloat("Orthographic Height", &AppSettings.OrthoHeight, 0.1f, 1.0f);
				ImGui::DragFloat("Near Plane", &AppSettings.NearPlane, 0.1f, 0.1f);
				ImGui::DragFloat("Far Plane", &AppSettings.FarPlane, 0.1f, 100.0f);
			}

			ImGui::End();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}

	printf("Shutting down...");
}