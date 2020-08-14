#pragma once
#include <glew.h>
#include <glfw3.h>

class Window 
{
private:
	GLFWwindow* mWindow;
	int width, height, nrChannels;
public:
	Window(int width, int height, const char* title);
	void setContextCurrent();
	void loop();
	~Window();
};