#include "VertexBuffer.h"

namespace PrimeEngine { namespace Graphics {

	VertexBuffer::VertexBuffer(const GLfloat* data, GLsizei count, GLuint componentCount) : _componentCount(componentCount)
	{
		glGenBuffers(1, &_index);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		Unbind();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &_index);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _index);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}}