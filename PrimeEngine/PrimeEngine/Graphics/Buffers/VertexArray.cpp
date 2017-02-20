#include "VertexArray.h"

namespace PrimeEngine { namespace Graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &_Id);
	}

	VertexArray::~VertexArray()
	{
		for (size_t i = 0; i < _buffers.size(); i++)
		{
			delete _buffers[i];
		}
		Unbind();
	}

	void VertexArray::AddBuffer(VertexBuffer* buffer, GLuint index)
	{
		Bind();
		_buffers.push_back(buffer);
		buffer->Bind();
		glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);
		buffer->Unbind();
		Unbind();
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(_Id);
	}

	void VertexArray::Unbind() const
	{
		glEnableVertexAttribArray(0);
	}

}}