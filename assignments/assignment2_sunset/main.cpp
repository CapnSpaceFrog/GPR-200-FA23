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
	-0.5, -0.5, 0.0,	0.0, 0.0,
	//Top Left
	-0.5, 0.5, 0.0,	0.0, 1.0,
	//Top Right
	0.5,  0.5, 0.0,	1.0, 1.0,
	//Bottom Right
	0.5, -0.5, 0.0,	1.0, 0.0,
};

unsigned int indices[] = {
	//Left hand side triangle
	0, 1, 2,
	//Right hand side triangle
	3, 2, 0
};

float triangleColor[3] = { 1.0f, 0.5f, 0.0f };
float triangleBrightness = 1.0f;
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

		//Set uniforms
		defaultShader.SetUniformVec3f("uColor", Vector3<float>(triangleColor[0], triangleColor[1], triangleColor[2]));
		defaultShader.SetUniform1f("uBrightness", triangleBrightness);

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
			ImGui::ColorEdit3("Color", triangleColor);
			ImGui::SliderFloat("Brightness", &triangleBrightness, 0.0f, 1.0f);
			ImGui::Checkbox("Wireframe Mode", &drawWireFrame);
			ImGui::Checkbox("Draw with Index", &drawWithIndex);
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