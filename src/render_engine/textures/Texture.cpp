#include "Texture.h"

RenderEngine::Texture::Texture(const std::string& texturePath)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	wrapTexture();
	loadTexture(texturePath);
	genTexture();
}

void RenderEngine::Texture::wrapTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void RenderEngine::Texture::loadTexture(const std::string& texturePath)
{
	data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
}

void RenderEngine::Texture::genTexture()
{
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void RenderEngine::Texture::useTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

RenderEngine::Texture::~Texture()
{
	stbi_image_free(data);
}
