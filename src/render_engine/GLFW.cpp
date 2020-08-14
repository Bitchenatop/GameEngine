#include "GLFW.h"

GLFW::GLFW()
{
	if (!glfwInit())
	{
		throw runtime_error("Could not initialize GLFW!");
		glfwTerminate();
	}
}

GLFW::~GLFW()
{
	glfwTerminate();
}