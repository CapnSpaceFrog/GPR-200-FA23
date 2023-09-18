#include <stdio.h>
#include <math.h>

#include <external/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GizmosLib/OpenGL/glHelpers.h"
#include "GizmosLib/OpenGL/shaderProgram.h"

using namespace GizmosLib::OpenGL;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	//x   //y  //z		//U	//V
	//Bottom Left
	-1.0, -1.0, 0.0,	0.0, 0.0,
	//Top Left
	-1.0, 1.0, 0.0,	0.0, 1.0,
	//Top Right
	1.0,  1.0, 0.0,	1.0, 1.0,
	//Bottom Right
	1.0, -1.0, 0.0,	1.0, 0.0,
};

unsigned int indices[] = {
	//Left hand side triangle
	0, 1, 2,
	//Right hand side triangle
	3, 2, 0
};

//BACKGROUND COLORS
float dayColorTop[3] = { 0.45f, 0.25f, 0.42f };
float dayColorBottom[3] = { 0.87f, 0.25f, 0.09f };
float nightColorTop[3] = { 0.875f, 0.33f, 0.40f };
float nightColorBottom[3] = { 0.16f, 0.13f, 0.39f };
float foregroundColor[3] = { 0.14f, 0.05f, 0.01f };

//SUN VARIABLES
float sunColorMax[3] = { 0.89f, 0.53f, 0.03f };
float sunColorMin[3] = { 0.72f, 0.32f, 0.15f };
float sunRadius = 0.35f;
float sunSpeed = 0.85f;

bool showImGUIDemoWindow = false;
bool drawWireFrame = false;
bool drawWithIndex = false;

int main()
{
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
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

	Shaders::ShaderProgram defaultShader(vertFilePath.c_str(), fragFilePath.c_str());

	unsigned int vao = generateVAO(vertices, 24, indices, 6);

	defaultShader.MakeActive();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//SET UNIFORMS
		//BACKGROUND COLORS
		defaultShader.SetUniformVec3f("uDayColorTop", Vector3<float>(dayColorBottom[0], dayColorBottom[1], dayColorBottom[2]));
		defaultShader.SetUniformVec3f("uDayColorBottom", Vector3<float>(dayColorTop[0], dayColorTop[1], dayColorTop[2]));
		defaultShader.SetUniformVec3f("uNightColorTop", Vector3<float>(nightColorTop[0], nightColorTop[1], nightColorTop[2]));
		defaultShader.SetUniformVec3f("uNightColorBottom", Vector3<float>(nightColorBottom[0], nightColorBottom[1], nightColorBottom[2]));
		defaultShader.SetUniformVec3f("uForegroundColor", Vector3<float>(foregroundColor[0], foregroundColor[1], foregroundColor[2]));

		//SUN UNIFORMS
		defaultShader.SetUniformVec3f("uSunColorMax", Vector3<float>(sunColorMax[0], sunColorMax[1], sunColorMax[2]));
		defaultShader.SetUniformVec3f("uSunColorMin", Vector3<float>(sunColorMin[0], sunColorMin[1], sunColorMin[2]));
		defaultShader.SetUniform1f("uSunRadius", sunRadius);
		defaultShader.SetUniform1f("uSunSpeed", sunSpeed);

		defaultShader.SetUniform1f("uTime", glfwGetTime());

		if (drawWithIndex)
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::Checkbox("Show Demo Window", &showImGUIDemoWindow);
			ImGui::Checkbox("Wireframe Mode", &drawWireFrame);
			ImGui::Checkbox("Draw with Index", &drawWithIndex);
			ImGui::ColorEdit3("Day Color Top", dayColorTop);
			ImGui::ColorEdit3("Day Color Bottom", dayColorBottom);
			ImGui::ColorEdit3("Night Color Top", nightColorTop);
			ImGui::ColorEdit3("Night Color Bottom", nightColorBottom);
			ImGui::ColorEdit3("Foreground Color", foregroundColor);
			ImGui::ColorEdit3("Sun Color Max", sunColorMax);
			ImGui::ColorEdit3("Sun Color Min", sunColorMin);
			ImGui::DragFloat("Sun Radius", &sunRadius, 1.0f, 0.0f, 2.0f);
			ImGui::DragFloat("Sun Speed", &sunSpeed, 1.0f, 0.0f, 2.0f);

			ImGui::End();
			if (showImGUIDemoWindow) {
				ImGui::ShowDemoWindow(&showImGUIDemoWindow);
			}

			if (drawWireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}