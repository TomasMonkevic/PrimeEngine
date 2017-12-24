#pragma once

#include <GL\glew.h>
#include "VertexBuffer.h"

namespace PrimeEngine { namespace Graphics {

	class VertexArray
	{
	private:
		GLuint _Id;

	public:
		VertexArray();
		~VertexArray();

		template<typename T>
		void AddAttribute(GLuint index, GLint componentCount, GLenum type, bool isNormalized, const GLvoid* offset)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, componentCount, type, isNormalized, sizeof(T), offset);
		}

		void Bind() const;
		void Unbind() const;
	};
}}