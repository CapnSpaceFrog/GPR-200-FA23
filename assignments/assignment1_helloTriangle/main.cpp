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
#include <fstream>
#include <sstream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

std::string vertFilePath = "Shaders/BasicVertex.vert";
std::string fragFilePath = "Shaders/BasicFrag.frag";

float vertices[] =
{
	//Model Coordinates			//Color
	//x		//y		//z		//R		//G		//B
	0.0f,		0.5f,		0.0f,		1.0f,		0.0f,		0.0f, //Top Center
	-0.5f,	-0.5f,	0.0f,		0.0f,		1.0f,		0.0f, //Bottom Left
	0.5f,		-0.5f,	0.0f,		0.0f,		0.0f,		1.0f,	//Bottom Right
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

	//VBO & VAO GENERATION AND BIND
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO = generateVAO(vertices, 18, VBO);

	//SHADER PROGRAM & UNIFORM ASSIGNMENT
	Shader basicShader(vertFilePath.c_str(), fragFilePath.c_str());
	
	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//CLEAR BACK BUFFER AND RESET COLOR
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//SET SHADER AS ACTIVE
		basicShader.MakeActive();
		//SET UNIFORM VALUE TO TIME
		basicShader.SetUniform1f("uTime", glfwGetTime());
		//BIND VAO AS ACTIVE
		glBindVertexArray(VAO);
		//DRAW CALL TO OPEN GL
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//SWAP THE BACK AND FRONT BUFFER
		glfwSwapBuffers(window);
	}

	//DELETE DATA AS APPLICATION CLOSES
	printf("Shutting down...");

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	basicShader.Delete();
	glfwTerminate();
	return 0;
}