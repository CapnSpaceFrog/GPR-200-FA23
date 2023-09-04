/*
	Name: Wyatt Llewellyn
	Date: 8/31/2023

	This work is mine and mine alone. No other individual assisted in the production
	of this project aside from Eric Winebrenner, the teacher of GPR-200.
*/

#include "glHelpers.h"
#include "shader.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] =
{
	//Model Coordinates			//Color
	//x		//y		//z		//R		//G		//B
	0.0f,		0.5f,		0.0f,		0.0f,		0.0f,		0.0f, //Top Center
	-0.5f,	-0.5f,	0.0f,		0.0f,		0.0f,		0.0f, //Bottom Left
	0.5f,		-0.5f,	0.0f,		0.0f,		0.0f,		0.0f,	//Bottom Right
};

int main()
{
	printf("Initializing...");

	//INITIALIZE GLFW
	if (!glfwInit())
	{
		printf("GLFW failed to init!");
		return 1;
	}

	//CREATE A WINDOW AND SET THE CURRENT OPENGL CONTEXT TO THE WINDOW
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL)
	{
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);

	//LOAD OPENGL HOOKS
	if (!gladLoadGL(glfwGetProcAddress))
	{
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//VAO
	//unsigned int VAO = generateVAO(vertices, 3);
	//VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VERTEX ATTRIBUTES
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//SHADER PROGRAM & UNIFORM ASSIGNMENT
	Shader basicShader("Shaders/BasicVertex.vert", "Shaders/BasicFrag.frag");

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.MakeActive();
		//basicShader.MakeActive();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	printf("Shutting down...");

	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	basicShader.Delete();
	glfwTerminate();
	return 0;
}