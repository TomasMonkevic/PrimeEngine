#include "IndexBuffer.h"

namespace PrimeEngine { namespace Graphics {

	IndexBuffer::IndexBuffer(const GLushort* data, GLsizei count) : _Count(count)
	{
		glGenBuffers(1, &_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Id);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}}