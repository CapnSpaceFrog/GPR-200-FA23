#include "GizmosLib/OpenGL/Core/Shaders/shaderProgram.h"
#include <external/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ew/ewMath/mat4.h>

using namespace GizmosLib::OpenGL::Core;

//Read shader source code from file, compile, then test compilation
//Create a shader program and attach vert and frag shaders then link together & check for errors
//Delete shaders after linked and compiled as they are no longer needed
ShaderProgram::ShaderProgram(const char* vertSourcePath, const char* fragSourcePath)
{
	//READ FROM FILE
	std::ifstream vertShaderFile, fragShaderFile;
	std::stringstream vertStream, fragStream;

	vertShaderFile.open(vertSourcePath);
	if (!vertShaderFile.is_open())
	{
		std::cout << "vert file did not open" << std::endl;
	}
	vertStream << vertShaderFile.rdbuf();
	vertShaderFile.close();

	//COMPILE SHADERS & ERROR CHECK
	//VERT SHADER
	std::string vertString = vertStream.str();
	const char* vertShaderSource = vertString.c_str();

	vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderID, 1, &vertShaderSource, NULL);

	glCompileShader(vertShaderID);
	int success;
	char infoLog[512];
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION::VERTEX" << infoLog << std::endl;
	}

	//FRAG SHADER
	fragShaderFile.open(fragSourcePath);
	if (!fragShaderFile.is_open())
	{
		std::cout << "frag file did not open" << std::endl;
	}
	fragStream << fragShaderFile.rdbuf();
	fragShaderFile.close();

	std::string fragString = fragStream.str();
	const char* fragShaderSource = fragString.c_str();

	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragShaderSource, NULL);

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

//FLOAT UNIFORM SETTERS
void ShaderProgram::SetUniform1f(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(programID, name), value);
}

void ShaderProgram::SetUniformVec2f(const char* name, Vector2<float> vec)
{
	glUniform2f(glGetUniformLocation(programID, name), vec.x, vec.y);
}

void ShaderProgram::SetUniformVec3f(const char* name, Vector3<float> vec)
{
	glUniform3f(glGetUniformLocation(programID, name), vec.x, vec.y, vec.z);
}

void ShaderProgram::SetUniformVec4f(const char* name, Vector4<float> vec)
{
	glUniform4f(glGetUniformLocation(programID, name), vec.x, vec.y, vec.z, vec.w);
}

//INT UNIFORM SETTERS
void ShaderProgram::SetUniform1i(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(programID, name), value);
}

void ShaderProgram::SetUniformVec2i(const char* name, Vector2<int> vec)
{
	glUniform2i(glGetUniformLocation(programID, name), vec.x, vec.y);
}

void ShaderProgram::SetUniformVec3i(const char* name, Vector3<int> vec)
{
	glUniform3i(glGetUniformLocation(programID, name), vec.x, vec.y, vec.z);
}

void ShaderProgram::SetUniformVec4i(const char* name, Vector4<int> vec)
{
	glUniform4i(glGetUniformLocation(programID, name), vec.x, vec.y, vec.z, vec.w);
}

//MATRIX UNIFORM SETTERS
void ShaderProgram::SetUniformMatrix(const char* name, ew::Mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, &mat[0][0]);
}

//UTILITY FUNCTIONS
void ShaderProgram::MakeActive()
{
	glUseProgram(programID);
}

void ShaderProgram::Delete()
{
	glDeleteProgram(programID);
}

//DESTRUCTOR
ShaderProgram::~ShaderProgram()
{
	Delete();
}