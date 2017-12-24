#pragma once

#include <GL\glew.h>

namespace PrimeEngine { namespace Graphics {

	template<typename T>
	class VertexBuffer
	{
	private:
		GLuint _index;

	public:
		VertexBuffer(const T* data, GLsizei count, GLenum usage)
		{
			glGenBuffers(1, &_index);
			Bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, usage);
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

		inline GLuint GetComponentCount() const
		{
			return _componentCount;
		}
	};

}}