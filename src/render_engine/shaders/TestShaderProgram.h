#pragma once

#include "glew.h"
#include "glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace RenderEngine
{
	class TestShaderProgram
	{

	private:
		unsigned int program;
		unsigned int vs;
		unsigned int fs;
	public:
		struct ShaderProgramSource
		{
			std::string vertexSource;
			std::string fragmentSource;
		};

		unsigned int getProgram()
		{
			return program;
		}

		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		TestShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~TestShaderProgram();
		void link();
		void use();
		void bindAttribute(GLuint index, const std::string& name);

		GLint getLocation(const std::string& name);
		void setFloat(const std::string& name, float anim);
		static ShaderProgramSource parseShader(const std::string& file);
	};
}

