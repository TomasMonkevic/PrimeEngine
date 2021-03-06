#pragma once

#include <DllExport.h>
#include <Graphics/OpenGL.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI IndexBuffer
	{
	private:
		GLuint _Id;
		GLuint _Count;
	public:
		IndexBuffer(const GLushort* data, GLsizei count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline GLuint GetCount() const 
		{
			return _Count;
		}
	};
}}