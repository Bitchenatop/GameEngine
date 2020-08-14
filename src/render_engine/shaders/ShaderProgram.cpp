#include "ShaderProgram.h"

RenderEngine::ShaderProgram::ShaderProgram(const string& name)
{
	mProgram = glCreateProgram();
	mVertexShader = loadShader("res/shaders/" + name + ".vert", GL_VERTEX_SHADER);
	mFragmentShader = loadShader("res/shaders/" + name + ".frag", GL_FRAGMENT_SHADER);
}

RenderEngine::ShaderProgram::~ShaderProgram()
{
	glDetachShader(mProgram, mVertexShader);
	glDetachShader(mProgram, mFragmentShader);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	glDeleteProgram(mProgram);
}

GLuint RenderEngine::ShaderProgram::loadShader(const string& path, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	// загрузка кода шейдера
	// выгл€дит страшно, но так проще, отвечаю
	ifstream fis(path);
	if (fis.is_open()) cout << "DA" << endl; else cout << "NET" << endl;
	// он посчитал, что это прототип функции (идиот просто), поэтому конструктор будет таким {}
	string shaderCode = { istreambuf_iterator<char>(fis), istreambuf_iterator<char>() };
	cout << shaderCode << endl;
	// загрузка кода шейдера в OpenGL
	const char* c = shaderCode.c_str();
	// да, тут именно указатель на указатель, char**
	glShaderSource(shader, 1, &c, nullptr);

	// получить результат компил€ции (успешно/неуспешно)
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	char buf[0x1000];
	GLsizei len;
	glGetShaderInfoLog(shader, sizeof(buf), &len, buf);
	if (len > 0)
	{
		std::cout << "Failed to compile shader " << path << ":" << std::endl << buf;
	}

	return shader;
}

void RenderEngine::ShaderProgram::link()
{
	glAttachShader(mProgram, mVertexShader);
	glAttachShader(mProgram, mFragmentShader);
	glLinkProgram(mProgram);
}

void RenderEngine::ShaderProgram::bindAttribute(GLuint index, const string& name)
{
	glBindAttribLocation(mProgram, index, name.c_str());
}

void RenderEngine::ShaderProgram::use()
{
	glUseProgram(mProgram);
}
