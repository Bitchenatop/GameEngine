#pragma once
#include <libs.h>

namespace RenderEngine
{
	class ShaderProgram
	{
	private:
		GLuint mProgram;
		GLuint mVertexShader;
		GLuint mFragmentShader;
	public:
		ShaderProgram(const string& name);
		~ShaderProgram();
		GLuint loadShader(const string& name, GLenum shaderType);
		void link();
		void bindAttribute(GLuint index, const string& name);
		void use();
	};
}
