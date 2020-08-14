#pragma once

#include "glew.h"
#include "glm.hpp"
#include "render_engine/shaders/TestShaderProgram.h"
class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	// timing
	float deltaTime;
	float lastFrame;
public:
	Camera(RenderEngine::TestShaderProgram program);
};