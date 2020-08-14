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

	// �������� ���� �������
	// �������� �������, �� ��� �����, �������
	ifstream fis(path);
	if (fis.is_open()) cout << "DA" << endl; else cout << "NET" << endl;
	// �� ��������, ��� ��� �������� ������� (����� ������), ������� ����������� ����� ����� {}
	string shaderCode = { istreambuf_iterator<char>(fis), istreambuf_iterator<char>() };
	cout << shaderCode << endl;
	// �������� ���� ������� � OpenGL
	const char* c = shaderCode.c_str();
	// ��, ��� ������ ��������� �� ���������, char**
	glShaderSource(shader, 1, &c, nullptr);

	// �������� ��������� ���������� (�������/���������)
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
