#include <ew/external/glad.h>
#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertSourcePath, std::string fragSourcePath)
{
	//READ FROM FILE
	std::ifstream vertShaderFile, fragShaderFile;
	std::stringstream vertStream, fragStream;

	vertShaderFile.open(vertSourcePath);
	vertStream << vertShaderFile.rdbuf();
	vertShaderFile.close();

	std::string vertString = vertStream.str();
	const char* vertShaderSource = vertString.c_str();

	vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderID, 1, &vertShaderSource, NULL);

	fragShaderFile.open(fragSourcePath);
	fragStream << fragShaderFile.rdbuf();
	fragShaderFile.close();

	std::string fragString = fragStream.str();
	const char* fragShaderSource = fragString.c_str();

	fragShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragShaderID, 1, &fragShaderSource, NULL);

	//COMPILE SHADERS & ERROR CHECK
	glCompileShader(vertShaderID);
	int success;
	char infoLog[512];
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION::VERTEX" << infoLog << std::endl;
	}

	glCompileShader(fragShaderID);
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION::FRAGMENT" << infoLog << std::endl;
	}

	//CREATE THE SHADER PROGRAM
	programID = glCreateProgram();

	glAttachShader(programID, vertShaderID);
	glAttachShader(programID, fragShaderID);
	glLinkProgram(programID);
	glGetShaderiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINK::BASIC_SHADER_PROG" << infoLog << std::endl;
	}

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);
}

void Shader::MakeActive()
{
	glUseProgram(programID);
}

void Shader::Delete()
{
	glDeleteProgram(programID);
}

Shader::~Shader()
{

}