/*
	Name: Wyatt Llewellyn
	Date: 8/31/2023

	This work is mine and mine alone. No other individual assisted in the production
	of this project aside from Eric Winebrenner, the teacher of GPR-200.
*/

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>

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

	//CREATE A WINDOW AND SET THE CURRENT CONTEXT TO THE WINDOW
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
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//SHADER PROGRAM
	std::ifstream vertShaderFile, fragShaderFile;
	std::stringstream vertStream, fragStream;
	vertShaderFile.open("Shaders/BasicVertex.vs");
	vertStream << vertShaderFile.rdbuf();
	vertShaderFile.close();

	std::string vertString = vertStream.str();
	const char* vertShaderSource = vertString.c_str();

	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShaderSource, NULL);

	fragShaderFile.open("Shaders/BasicVertex.vs");
	fragStream << fragShaderFile.rdbuf();
	fragShaderFile.close();

	std::string fragString = fragStream.str();
	const char* fragShaderSource = fragString.c_str();

	unsigned int fragShader;
	fragShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);

	glCompileShader(vertShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION::VERTEX" << infoLog << std::endl;
	}
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION::FRAGMENT" << infoLog << std::endl;
	}

	unsigned int basicShaderProg;
	basicShaderProg = glCreateProgram();

	glAttachShader(basicShaderProg, vertShader);
	glAttachShader(basicShaderProg, fragShader);
	glLinkProgram(basicShaderProg);
	glGetShaderiv(basicShaderProg, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(basicShaderProg, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINK::BASIC_SHADER_PROG" << infoLog << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	//VERTEX ATTRIBUTES
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );

	//UNIFORM ASSIGNMENT


	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(basicShaderProg);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	printf("Shutting down...");

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
