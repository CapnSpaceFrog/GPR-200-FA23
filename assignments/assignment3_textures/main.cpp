#include <stdio.h>
#include <math.h>

#include <external/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GizmosLib/OpenGL/shaderProgram.h"
#include "GizmosLib/OpenGL/glHelpers.h"

const std::string backgroundTexPath = "assets/background.png";
const std::string noiseTexPath = "assets/noise.png";
const std::string tilingTexPath = "assets/tiling.png";
const std::string characterTexPath = "assets/frog.png";

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[20] =
{
	-1.0,	 -1.0,	0.0,	 0.0,	 0.0,
	1.0,	 -1.0,	0.0,	 1.0,	 0.0,
	1.0,	 1.0,		0.0,	 1.0,	 1.0,
	-1.0,	 1.0,		0.0,	 0.0,	 1.0,
};

unsigned int indices[6] =
{
	0, 1, 2,
	2, 3, 0
};

int main() {
	printf("Initializing...");

	if (!glfwInit())
	{
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures", NULL, NULL);
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

	GizmosLib::OpenGL::Shaders::ShaderProgram backgroundShader("assets/backgroundVert.vert", "assets/backgroundFrag.frag");

	GizmosLib::OpenGL::Shaders::ShaderProgram characterShader("assets/characterVert.vert", "assets/characterFrag.frag");

	//fix this shit bruh
	unsigned int quadVAO = GizmosLib::OpenGL::generateVAO(vertices, 20, indices, 6);

	unsigned int characterTexture = GizmosLib::OpenGL::loadTexture(characterTexPath.c_str(), GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	unsigned int backgroundTexture = GizmosLib::OpenGL::loadTexture(backgroundTexPath.c_str(), GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
	unsigned int noiseTexture = GizmosLib::OpenGL::loadTexture(noiseTexPath.c_str(), GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE);
	unsigned int tilingTexture = GizmosLib::OpenGL::loadTexture(tilingTexPath.c_str(), GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

	//ENABLE BLENDING
	glEnable(GL_BLEND);
	//The formula OpenGL uses to blend colors together
	//ResultColor = SourceColor * SourceFactor + DestinationColor * DestinationFactor
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//BIND ACTIVE VAO
		glBindVertexArray(quadVAO);

		//BIND BACKGROUND TEXTURE
		backgroundShader.MakeActive();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, backgroundTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, tilingTexture);

		//SET BACKGROUND SHADER UNIFORMS
		backgroundShader.SetUniform1i("uBackgroundTexture", 0);
		backgroundShader.SetUniform1i("uNoiseTexture", 1);
		backgroundShader.SetUniform1i("uTilingTexture", 2);
		backgroundShader.SetUniform1f("uTime", glfwGetTime());

		//DRAW BACKGROUND
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		//BIND CHARACTER TEXTURE
		characterShader.MakeActive();
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, characterTexture);

		//SET CHARACTER SHADER UNIFORMS
		characterShader.SetUniform1i("uCharacterTexture", 3);
		characterShader.SetUniform1f("uCharacterScale", 0.5);
		characterShader.SetUniform1f("uTime", glfwGetTime());

		//DRAW CHARACTER
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			//INPUT ALL IMGUI UNIFORM CONTROLS HERE
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}