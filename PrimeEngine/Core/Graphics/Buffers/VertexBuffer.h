#pragma once

#include <Graphics/OpenGL.h>
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI VertexBuffer
	{
	private:
		GLuint _index;

	public:
		VertexBuffer(const void* data, GLsizei size, GLenum usage)
		{
			GlCall(glGenBuffers(1, &_index));
			Bind();
			GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
			Unbind();
		}

		~VertexBuffer()
		{
			GlCall(glDeleteBuffers(1, &_index));
		}

		void Bind() const
		{
			GlCall(glBindBuffer(GL_ARRAY_BUFFER, _index));
		}

		void Unbind() const
		{
			GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
	};

}}