#include "Window.h"
#include "VAO/VAO.h"
#include "textures/Texture.h"
#include "shaders/TestShaderProgram.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Window::Window(int width, int height, const char* title)
{
	mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!mWindow)
	{
		throw std::runtime_error("Could not initialize window");
	}
	setContextCurrent();
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Could not initialize GLEW");
	}
}

void Window::setContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

void Window::loop()
{

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	RenderEngine::Texture texture("res/textures/wall.jpg");

	RenderEngine::VAO vao;

	//Позиции вершин
	vao.addVertexBufferObject
	({
		{-0.5f,0.5f,-0.5f},{-0.5f,-0.5f,-0.5f},{0.5f,-0.5f,-0.5f},{0.5f,0.5f,-0.5f},
		{-0.5f,0.5f,0.5f}, {-0.5f,-0.5f,0.5f}, {0.5f,-0.5f,0.5f}, {0.5f,0.5f,0.5f},
		{0.5f,0.5f,-0.5f}, {0.5f,-0.5f,-0.5f},  {0.5f,-0.5f,0.5f}, {0.5f,0.5f,0.5f},
		{-0.5f,0.5f,-0.5f},{-0.5f,-0.5f,-0.5f},{-0.5f,-0.5f,0.5f},{-0.5f,0.5f,0.5f},
		{-0.5f,0.5f,0.5f}, {-0.5f,0.5f,-0.5f},  {0.5f,0.5f,-0.5f}, {0.5f,0.5f,0.5f},
		{-0.5f,-0.5f,0.5f},{-0.5f,-0.5f,-0.5f},{0.5f,-0.5f,-0.5f},{0.5f,-0.5f,0.5f}
	});

	//Текстурные координаты
	texture.useTexture();
	vao.addVertexBufferObject
	({
		{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},{1,0},
		{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},{1,0}
	});

	vao.addIndices
	({
		0,1,3,3,1,2,4,5,7,7,5,6,8,9,11,11,9,10,12,13,15,15,13,14,16,17,19,19,17,18,20,21,23,23,21,22
	});

	RenderEngine::TestShaderProgram::ShaderProgramSource source = RenderEngine::TestShaderProgram::parseShader("res/shaders/Basic.shader");
	std::string vs = source.vertexSource;
	std::string fs = source.fragmentSource;
	
	RenderEngine::TestShaderProgram shader(vs, fs);
	shader.bindAttribute(0, "aPos");	
	shader.bindAttribute(1, "aTexCoord");
	shader.use();

	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;

	while (!glfwWindowShouldClose(mWindow))
	{
		if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(mWindow, true);

		float cameraSpeed = 2.5 * deltaTime;
		if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.5f, 0.5f, 0.5f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		unsigned int modelLoc = glGetUniformLocation(shader.getProgram(), "model");
		unsigned viewLoc = glGetUniformLocation(shader.getProgram(), "view");
		unsigned projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glEnable(GL_DEPTH_TEST);
		vao.draw();
		glDisable(GL_DEPTH_TEST);

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
		
	}
}

Window::~Window()
{
	glfwDestroyWindow(mWindow);
}
