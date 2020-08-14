#include "TestShaderProgram.h"

unsigned int RenderEngine::TestShaderProgram::compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// да, тут именно указатель на указатель, char**
	glShaderSource(id, 1, &src, nullptr);

	// получить результат компил€ции (успешно/неуспешно)
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	char buf[0x1000];
	GLsizei len;
	glGetShaderInfoLog(id, sizeof(buf), &len, buf);
	if (len > 0)
	{
		std::cout << "Failed to compile shader " << buf << std::endl;;
	}

	return id;
}

unsigned int RenderEngine::TestShaderProgram::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	program = glCreateProgram();
	vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	link();

	return program;
}

RenderEngine::TestShaderProgram::TestShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	createShader(vertexShader, fragmentShader);
}

void RenderEngine::TestShaderProgram::link()
{
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
}

void RenderEngine::TestShaderProgram::bindAttribute(GLuint index, const std::string& name)
{
	glBindAttribLocation(program, index, name.c_str());
}

GLint RenderEngine::TestShaderProgram::getLocation(const std::string& name)
{
	return glGetUniformLocation(program, name.c_str());
}

void RenderEngine::TestShaderProgram::setFloat(const std::string& name, float anim)
{
	glUniform1f(getLocation(name), anim);
}

RenderEngine::TestShaderProgram::ShaderProgramSource
RenderEngine::TestShaderProgram::parseShader(const std::string& file)
{
	std::ifstream stream(file);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}


void RenderEngine::TestShaderProgram::use()
{
	glUseProgram(program);
}

RenderEngine::TestShaderProgram::~TestShaderProgram()
{
	glDetachShader(program, vs);
	glDetachShader(program, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}