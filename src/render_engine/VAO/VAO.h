#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <vector>

namespace RenderEngine
{
	class VAO
	{
	private:
		GLuint mVao;
		std::vector<GLuint> mBuffers;
		unsigned mIndicesBuffer = 0;
		size_t mIndicesCount = 0;
	public:
		VAO();
		VAO(const VAO&) = delete;
		void bind();
		void draw(unsigned type = GL_TRIANGLES);
		void addVertexBufferObject(const std::vector<float>& data);
		void addVertexBufferObject(const std::vector<glm::vec2>& data);
		void addVertexBufferObject(const std::vector<glm::vec3>& data);
		void addVertexBufferObject(const std::vector<glm::vec4>& data);
		void addIndices(const std::vector<unsigned>& data);
		~VAO();
	};
}
