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

struct AnimProps
{
	AnimProps() {};
	AnimProps(std::string name, int fps, float length, Animation* anim)
		: Name(name), FPS(fps), Length(length), BoundAnim(anim) {};

	Animation* BoundAnim;
	std::string Name;
	int FPS;
	float Length;
};

AnimProps AnimProperties[4];

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

	//Create Steampunk Assets
	
	Sprite* mysterManDefault = new Sprite(*SteampunkSpriteSheet, ew::Vec2(0, 96), 32);
	Sprite* mysteryManSprites[] = {
		mysterManDefault,
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(32, 96), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(64, 96), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(96, 96), 32),
	};
	Animation* mysteryManIdle = new Animation(mysteryManSprites, 4, 12, 5.0f, true);
	AnimProperties[0] = AnimProps("Myster Man", 12, 5.0f, mysteryManIdle);

	Sprite* bartenderDefault = new Sprite(*SteampunkSpriteSheet, ew::Vec2(0, 64), 32);
	Sprite* bartenderSprites[] = {
		bartenderDefault,
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(32, 64), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(64, 64), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(96, 64), 32),
	};
	Animation* bartenderIdle = new Animation(bartenderSprites, 4, 12, 5.0f, true);
	AnimProperties[1] = AnimProps("Bartender", 12, 5.0f, bartenderIdle);
	
	Sprite* shadyGuyDefault = new Sprite(*SteampunkSpriteSheet, ew::Vec2(0, 32), 32);
	Sprite* shadyGuySprites[] = {
		shadyGuyDefault,
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(32, 32), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(64, 32), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(96, 32), 32),
	};
	Animation* shadyGuyIdle = new Animation(shadyGuySprites, 4, 12, 5.0f, true);
	AnimProperties[2] = AnimProps("Shady Guy", 12, 5.0f, shadyGuyIdle);

	Sprite* suaveDefault = new Sprite(*SteampunkSpriteSheet, ew::Vec2(0, 0), 32);
	Sprite* suaveSprites[] = {
		suaveDefault,
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(32, 0), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(64, 0), 32),
		new Sprite(*SteampunkSpriteSheet, ew::Vec2(96, 0), 32),
	};
	Animation* suaveIdle = new Animation(suaveSprites, 4, 12, 5.0f, true);
	AnimProperties[3] = AnimProps("Suave Guy", 12, 5.0f, suaveIdle);

	//Create Elemental Assets
	Sprite* wandererDefault = new Sprite(*ElementalSpriteSheet, ew::Vec2(0, 96), 32);
	Sprite* wandererSprites[] = {
		wandererDefault,
		new Sprite(*ElementalSpriteSheet, ew::Vec2(32, 96), 32),
		new Sprite(*ElementalSpriteSheet,ew::Vec2(64, 96), 32),
		new Sprite(*ElementalSpriteSheet, ew::Vec2(96, 96), 32),
	};
	Animation wandererIdle = Animation(wandererSprites, 4, 12, 3.2f, true);

	Sprite* rougueDefault = new Sprite(*ElementalSpriteSheet, ew::Vec2(0, 64), 32);
	Sprite* rougueSprites[] = {
		rougueDefault,
		new Sprite(*ElementalSpriteSheet, ew::Vec2(32, 64), 32),
		new Sprite(*ElementalSpriteSheet,ew::Vec2(64, 64), 32),
		new Sprite(*ElementalSpriteSheet, ew::Vec2(96, 64), 32),
	};
	Animation rougueIdle = Animation(rougueSprites, 4, 12, 3.2f, true);

	Sprite* archerDefault = new Sprite(*ElementalSpriteSheet, ew::Vec2(0, 32), 32);
	Sprite* archerSprites[] = {
		archerDefault,
		new Sprite(*ElementalSpriteSheet, ew::Vec2(32, 32), 32),
		new Sprite(*ElementalSpriteSheet,ew::Vec2(64, 32), 32),
		new Sprite(*ElementalSpriteSheet, ew::Vec2(96, 32), 32),
	};
	Animation archerIdle = Animation(archerSprites, 4, 12, 3.2f, true);

	Sprite* priestDefault = new Sprite(*ElementalSpriteSheet, ew::Vec2(0, 0), 32);
	Sprite* priestSprites[] = {
		priestDefault,
		new Sprite(*ElementalSpriteSheet, ew::Vec2(32, 0), 32),
		new Sprite(*ElementalSpriteSheet,ew::Vec2(64, 0), 32),
		new Sprite(*ElementalSpriteSheet, ew::Vec2(96, 0), 32),
	};
	Animation priestIdle = Animation(priestSprites, 4, 12, 3.2f, true);

	//Create Medieval Assets
	Sprite* witchDefault = new Sprite(*MedievalSpriteSheet, ew::Vec2(0, 96), 32);
	Sprite* witchSprites[] = {
		witchDefault,
		new Sprite(*MedievalSpriteSheet, ew::Vec2(32, 96), 32),
		new Sprite(*MedievalSpriteSheet,ew::Vec2(64, 96), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(96, 96), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(128, 96), 32)
	};
	Animation witchIdle = Animation(witchSprites, 5, 12, 3.2f, true);

	Sprite* maidenDefault = new Sprite(*MedievalSpriteSheet, ew::Vec2(0, 64), 32);
	Sprite* maidenSprites[] = {
		maidenDefault,
		new Sprite(*MedievalSpriteSheet, ew::Vec2(32, 64), 32),
		new Sprite(*MedievalSpriteSheet,ew::Vec2(64, 64), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(96, 64), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(128, 64), 32),
	};
	Animation maidenIdle = Animation(maidenSprites, 5, 12, 3.2f, true);

	Sprite* farmerDefault = new Sprite(*MedievalSpriteSheet, ew::Vec2(0, 32), 32);
	Sprite* farmerSprites[] = {
		farmerDefault,
		new Sprite(*MedievalSpriteSheet, ew::Vec2(32, 32), 32),
		new Sprite(*MedievalSpriteSheet,ew::Vec2(64, 32), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(96, 32), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(128, 32), 32),
	};
	Animation farmerIdle = Animation(farmerSprites, 5, 12, 3.2f, true);

	Sprite* merchantDefault = new Sprite(*MedievalSpriteSheet, ew::Vec2(0, 0), 32);
	Sprite* merchantSprites[] = {
		merchantDefault,
		new Sprite(*MedievalSpriteSheet, ew::Vec2(32, 0), 32),
		new Sprite(*MedievalSpriteSheet,ew::Vec2(64, 0), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(96, 0), 32),
		new Sprite(*MedievalSpriteSheet, ew::Vec2(128, 0), 32),
	};
	Animation merchantIdle = Animation(merchantSprites, 5, 12, 3.2f, true);

	//Create Steampunk Objects
	GameObject mysterManObj = GameObject();
	mysterManObj.Transform.Position = ew::Vec3(-1, 1, 0);
	mysterManObj.SetDefaultSprite(*mysterManDefault);
	mysterManObj.SetActiveAnimation(*mysteryManIdle);

	GameObject bartenderObj = GameObject();
	bartenderObj.Transform.Position = ew::Vec3(1, 1, 0);
	bartenderObj.SetDefaultSprite(*bartenderDefault);
	bartenderObj.SetActiveAnimation(*bartenderIdle);

	GameObject shadyGuyObj = GameObject();
	shadyGuyObj.Transform.Position = ew::Vec3(1, -1, 0);
	shadyGuyObj.SetDefaultSprite(*shadyGuyDefault);
	shadyGuyObj.SetActiveAnimation(*shadyGuyIdle);

	GameObject suaveGuyObj = GameObject();
	suaveGuyObj.Transform.Position = ew::Vec3(-1, -1, 0);
	suaveGuyObj.SetDefaultSprite(*suaveDefault);
	suaveGuyObj.SetActiveAnimation(*suaveIdle);

	//Create Elemental Objects
	GameObject wandererObj = GameObject();
	wandererObj.Transform.Position = ew::Vec3(7, 1, 0);
	wandererObj.SetDefaultSprite(*wandererDefault);
	wandererObj.SetActiveAnimation(wandererIdle);

	GameObject rougueObj = GameObject();
	rougueObj.Transform.Position = ew::Vec3(5, 1, 0);
	rougueObj.SetDefaultSprite(*rougueDefault);
	rougueObj.SetActiveAnimation(rougueIdle);

	GameObject archerObj = GameObject();
	archerObj.Transform.Position = ew::Vec3(5, -1, 0);
	archerObj.SetDefaultSprite(*archerDefault);
	archerObj.SetActiveAnimation(archerIdle);

	GameObject priestObj = GameObject();
	priestObj.Transform.Position = ew::Vec3(7, -1, 0);
	priestObj.SetDefaultSprite(*priestDefault);
	priestObj.SetActiveAnimation(priestIdle);
	
	//Create Medieval Objects
	GameObject witchObj = GameObject();
	witchObj.Transform.Position = ew::Vec3(-7, 1, 0);
	witchObj.SetDefaultSprite(*witchDefault);
	witchObj.SetActiveAnimation(witchIdle);

	GameObject maidenObj = GameObject();
	maidenObj.Transform.Position = ew::Vec3(-5, 1, 0);
	maidenObj.SetDefaultSprite(*maidenDefault);
	maidenObj.SetActiveAnimation(maidenIdle);

	GameObject farmerObj = GameObject();
	farmerObj.Transform.Position = ew::Vec3(-5, -1, 0);
	farmerObj.SetDefaultSprite(*farmerDefault);
	farmerObj.SetActiveAnimation(farmerIdle);

	GameObject merchantObj = GameObject();
	merchantObj.Transform.Position = ew::Vec3(-7, -1, 0);
	merchantObj.SetDefaultSprite(*merchantDefault);
	merchantObj.SetActiveAnimation(merchantIdle);

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

		//Steampunk Batch
		mysterManObj.Render();
		bartenderObj.Render();
		shadyGuyObj.Render();
		suaveGuyObj.Render();

		SpriteBatcher::GetInstance().DrawBatch();
		
		//Batch Elemental Batch
		wandererObj.Render();
		rougueObj.Render();
		archerObj.Render();
		priestObj.Render();

		SpriteBatcher::GetInstance().DrawBatch();

		//Batch Medieval Batch
		witchObj.Render();
		maidenObj.Render();
		farmerObj.Render();
		merchantObj.Render();

		SpriteBatcher::GetInstance().DrawBatch();

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");

			if (ImGui::CollapsingHeader("Camera"))
				ImGui::DragFloat("Orthographic Height", &AppSettings.OrthoHeight, 0.1f, 1.0f);

			for (int i = 0; i < 4; i++)
			{
				ImGui::PushID(i);
				
				if (ImGui::CollapsingHeader(AnimProperties[i].Name.c_str()))
				{
					if (ImGui::DragInt("FPS", &AnimProperties[i].FPS, 1, 1.0f, 60.0f))
						AnimProperties[i].BoundAnim->SetFPS(AnimProperties[i].FPS);

					if (ImGui::DragFloat("Length", &AnimProperties[i].Length, 0.15f, 1.0f))
						AnimProperties[i].BoundAnim->SetLength(AnimProperties[i].Length);
				}

				ImGui::PopID();
			}
			
			ImGui::End();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}

	printf("Shutting down...");
}