#pragma once

#include <GL/glew.h>
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI VertexBuffer
	{
	private:
		GLuint _index;

	public:
		VertexBuffer(const void* data, GLsizei size, GLenum usage)
		{
			glGenBuffers(1, &_index);
			Bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
			Unbind();
		}

		~VertexBuffer()
		{
			glDeleteBuffers(1, &_index);
		}

		void Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, _index);
		}

		void Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};

}}