#include "IndexBuffer.h"

namespace PrimeEngine { namespace Graphics {

	IndexBuffer::IndexBuffer(const GLushort* data, GLsizei count) : _Count(count)
	{
		GlCall(glGenBuffers(1, &_Id));
		Bind();
		GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW));
		Unbind();
	}

	IndexBuffer::~IndexBuffer()
	{
		GlCall(glDeleteBuffers(1, &_Id));
	}

	void IndexBuffer::Bind() const
	{
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Id));
	}

	void IndexBuffer::Unbind() const
	{
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}}