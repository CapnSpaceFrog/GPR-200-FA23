#include <stdio.h>
#include <math.h>
#include <string>

#include <external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/shader.h>
#include <ew/procGen.h>
#include <ew/transform.h>

#include "GizmosLib/OpenGL/glHelpers.h"
#include "GizmosLib/Sprite/Sprite.h"
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

	unsigned int MedievalSpriteSheet = GizmosLib::OpenGL::loadTexture("assets/Sprite Sheets/MedievalTownfolkSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 medievalSpriteSize = { 0, 0};
	unsigned int ElementalSpriteSheet = GizmosLib::OpenGL::loadTexture("assets/Sprite Sheets/ElementalWarriorsSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 elementalSpriteSize = { 0, 0 };
	unsigned int SteampunkSpriteSheet = GizmosLib::OpenGL::loadTexture("assets/Sprite Sheets/SteampunkCharacterSheet.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	ew::Vec2 steampunkSpriteSize = { 0, 0 };

	GizmosLib::OpenGL::Sprite::Sprite testSprite = GizmosLib::OpenGL::Sprite::Sprite(0, 96, 128, 128, 32);

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

		testSprite.Draw(ew::DrawMode::TRIANGLES);

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