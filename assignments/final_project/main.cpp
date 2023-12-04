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
#include "GizmosLib/GameObject/gameObject.h"

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

	//Default Shader
	ShaderProgram defaultUnlit("assets/unLit.vert", "assets/unLit.frag");

	//Load Sprite Sheets (Should really become their own class called texture with some helper functions)
	unsigned int MedievalSpriteSheet = GizmosLib::OpenGL::Utility::loadTexture("assets/Sprite Sheets/MedievalTownfolkSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 medievalSpriteSize = { 0, 0};
	unsigned int ElementalSpriteSheet = GizmosLib::OpenGL::Utility::loadTexture("assets/Sprite Sheets/ElementalWarriorsSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 elementalSpriteSize = { 128, 128 };
	unsigned int SteampunkSpriteSheet = GizmosLib::OpenGL::Utility::loadTexture("assets/Sprite Sheets/SteampunkCharacterSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 steampunkSpriteSize = { 128, 128 };

	//TESTING
	Sprite priest1 = Sprite(ew::Vec2(0, 0), elementalSpriteSize, 32, ElementalSpriteSheet);
	Sprite priest2 = Sprite(ew::Vec2(32, 0), elementalSpriteSize, 32, ElementalSpriteSheet);
	Sprite priest3 = Sprite(ew::Vec2(64, 0), elementalSpriteSize, 32, ElementalSpriteSheet);
	Sprite priest4 = Sprite(ew::Vec2(96, 0), elementalSpriteSize, 32, ElementalSpriteSheet);

	Sprite priestSprites[] = { priest1, priest2, priest3, priest4 };
	Animation elementalPriestIdle = Animation(priestSprites, 4, 12, 3.2f, true);

	Sprite mysteryMan1 = Sprite(ew::Vec2(0, 96), steampunkSpriteSize, 32, SteampunkSpriteSheet);
	Sprite mysteryMan2 = Sprite(ew::Vec2(32, 96), steampunkSpriteSize, 32, SteampunkSpriteSheet);
	Sprite mysteryMan3 = Sprite(ew::Vec2(64, 96), steampunkSpriteSize, 32, SteampunkSpriteSheet);
	Sprite mysteryMan4 = Sprite(ew::Vec2(96, 96), steampunkSpriteSize, 32, SteampunkSpriteSheet);

	Sprite mysteryManSprites[] = { mysteryMan1, mysteryMan2, mysteryMan3, mysteryMan4 };
	Animation mysteryManIdle = Animation(mysteryManSprites, 4, 12, 5.0f, true);
	
	GameObject testObj = GameObject();
	GameObject testObj2 = GameObject();

	testObj.SetDefaultSprite(priest1);
	testObj.SetActiveAnimation(elementalPriestIdle);

	testObj2.SetDefaultSprite(mysteryMan1);
	testObj2.SetActiveAnimation(mysteryManIdle);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//Glfw returns seconds
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

		defaultUnlit.SetUniformMatrix("_View", LookAt(ew::Vec3(0, 0, 5), ew::Vec3(0, 0, 0), ew::Vec3(0, 1, 0)));

		testObj.Render();
		
		testObj2.Render();

		//Close spritebatcher here

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