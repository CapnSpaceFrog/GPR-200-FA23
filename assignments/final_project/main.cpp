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
#include <GizmosLib/OpenGL/SpriteBatcher/spriteBatcher.h>
#include "GizmosLib/Transforms/Object/transforms.h"
#include "GizmosLib/Transforms/Camera/camera.h"
#include "GizmosLib/Engine/GameObject/gameObject.h"

#include <GizmosLib/Engine/Time/time.h>

using namespace GizmosLib::Transforms;
using namespace GizmosLib::OpenGL::Core;
using namespace GizmosLib::OpenGL::Utility;

using namespace GizmosLib::Engine::Core;

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

	//Load Sprite Sheets
	Texture* MedievalSpriteSheet = new Texture("assets/Sprite Sheets/MedievalTownfolkSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT);
	Texture* ElementalSpriteSheet = new Texture("assets/Sprite Sheets/ElementalWarriorsSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT);
	Texture* SteampunkSpriteSheet = new Texture("assets/Sprite Sheets/SteampunkCharacterSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT);

	//TESTING
	Sprite* priestSprites[] = {
		new Sprite(*ElementalSpriteSheet, ew::Vec2(0, 0), 32),
		new Sprite(*ElementalSpriteSheet, ew::Vec2(32, 0), 32),
		new Sprite(*ElementalSpriteSheet,ew::Vec2(64, 0), 32),
		new Sprite(*ElementalSpriteSheet, ew::Vec2(96, 0), 32),
	};
	Animation elementalPriestIdle = Animation(priestSprites, 4, 12, 3.2f, true);

	Sprite* mysterManDefault = new Sprite(*SteampunkSpriteSheet, ew::Vec2(0, 96), 32);
	Sprite* mysteryManSprites[] = {
		mysterManDefault,
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(32, 96), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(64, 96), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(96, 96), 32),
	};
	Animation mysteryManIdle = Animation(mysteryManSprites, 4, 12, 5.0f, true);

	Sprite* bartenderDefault = new Sprite(*SteampunkSpriteSheet, ew::Vec2(0, 64), 32);
	Sprite* bartenderSprites[] = {
		bartenderDefault,
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(32, 64), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(64, 64), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(96, 64), 32),
	};
	Animation bartenderIdle = Animation(bartenderSprites, 4, 12, 5.0f, true);
	
	GameObject testObj = GameObject();
	testObj.Transform.Position = ew::Vec3(-2, 0, 0);

	GameObject testObj2 = GameObject();
	testObj2.Transform.Position = ew::Vec3(2, 0, 0);

	testObj.SetActiveAnimation(mysteryManIdle);
	testObj.SetDefaultSprite(*mysterManDefault);

	testObj2.SetDefaultSprite(*bartenderDefault);
	testObj2.SetActiveAnimation(bartenderIdle);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//Update Global Time
		Time::Update();

		//RENDER BACKGROUND
		glClearColor(bgColor.x, bgColor.y,bgColor.z,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultUnlit.MakeActive();

		defaultUnlit.SetUniformMatrix("_OrthoProjection", Orthographic(AppSettings.OrthoHeight,
			((float)GizmosLib::OpenGL::Utility::SCREEN_WIDTH / (float)GizmosLib::OpenGL::Utility::SCREEN_HEIGHT),
			AppSettings.NearPlane,
			AppSettings.FarPlane));

		defaultUnlit.SetUniformMatrix("_View", LookAt(ew::Vec3(0, 0, 5), ew::Vec3(0, 0, 0), ew::Vec3(0, 1, 0)));

		defaultUnlit.SetUniform1i("uSpriteSheet", 0);

		testObj.Render();
		testObj2.Render();

		SpriteBatcher::GetInstance().DrawBatch();

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