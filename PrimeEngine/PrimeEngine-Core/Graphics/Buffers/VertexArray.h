#pragma once

#include <GL/glew.h>
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
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, componentCount, type, isNormalized, size, offset);
		}

		void Bind() const;
		void Unbind() const;
	};
}}