#ifndef SHADER_CLASS
#define SHADER_CLASS

#include "GizmosLib/Math/vector.h"
#include <ew/ewMath/mat4.h>

using namespace GizmosLib::Math;

namespace GizmosLib { namespace OpenGL 
{
	namespace Shaders
	{
		class ShaderProgram
		{
		public:
			unsigned int programID;

			ShaderProgram();

			ShaderProgram(const char* vertSourcePath, const char* fragSourcePath);

			void SetUniform1f(const char* name, float value) const;
			void SetUniform1i(const char* name, int value) const;

			void SetUniformVec2f(const char* name, Vector2<float> vec);
			void SetUniformVec3f(const char* name, Vector3<float> vec);
			void SetUniformVec4f(const char* name, Vector4<float> vec);

			void SetUniformVec2i(const char* name, Vector2<int> vec);
			void SetUniformVec3i(const char* name, Vector3<int> vec);
			void SetUniformVec4i(const char* name, Vector4<int> vec);

			void SetUniformMatrix(const char* name, ew::Mat4& mat);

			//Stub functions that are not used yet
			void AttachShader();
			void DetatchShader();

			void MakeActive();
			void Delete();

			~ShaderProgram();

		private:

			unsigned int vertShaderID;
			unsigned int fragShaderID;
		};
	}
} }

#endif