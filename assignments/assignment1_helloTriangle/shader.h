#ifndef SHADER_CLASS
#define SHADER_CLASS

class Shader
{
public:
	unsigned int programID;

	Shader();

	Shader(const char* vertSourcePath, const char* fragSourcePath);

	void SetUniform1f(const char* name, float value);

	void AttachShader();
	void DetatchShader();

	void MakeActive();
	void Delete();

	~Shader();

private:
	
	unsigned int vertShaderID;
	unsigned int fragShaderID;
};

#endif