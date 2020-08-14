#pragma once

#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include <string>
#include <iostream>

namespace RenderEngine
{
	class Texture
	{
	private:
		unsigned int texture;
		stbi_uc* data;
		int width, height, nrChannels;
	public:
		Texture(const std::string& texturePath);
		void wrapTexture();
		void loadTexture(const std::string& texturePath);
		void genTexture();
		void useTexture();
		~Texture();
	};
}

