#pragma once

#ifdef PE_ANDROID
	#include <EGL/egl.h>
	#include <gl3stub.h>
#else
	#include <GL/glew.h>
#endif
#include <DllExport.h>

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