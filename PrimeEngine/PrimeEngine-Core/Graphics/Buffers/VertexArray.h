#pragma once

#include <Graphics/OpenGL.h>
#include "VertexBuffer.h"
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI VertexArray
	{
	private:
		GLuint _Id;

	public:
		VertexArray();
		~VertexArray();

		void AddAttribute(GLuint index, GLint componentCount, GLenum type, bool isNormalized, GLsizei size,  const GLvoid* offset)
		{
			GlCall(glEnableVertexAttribArray(index));
			GlCall(glVertexAttribPointer(index, componentCount, type, isNormalized, size, offset));
		}

		void Bind() const;
		void Unbind() const;
	};
}}