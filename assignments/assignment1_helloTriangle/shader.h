#ifndef SHADER_CLASS
#define SHADER_CLASS

#include <string>

class Shader
{
public:
	Shader();

	Shader(std::string vertSourcePath, std::string fragSourcePath);

	void AttachShader();
	void DetatchShader();

	void MakeActive();
	void Delete();

	~Shader();

private:
	unsigned int programID;
	unsigned int vertShaderID;
	unsigned int fragShaderID;
};

#endif