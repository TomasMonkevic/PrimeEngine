#include "VertexArray.h"

namespace PrimeEngine { namespace Graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &_Id);
	}

	VertexArray::~VertexArray()
	{
		//for (int i = 0; i < _buffers.size; i++)
		//{
		//	delete _buffers[i];
		//}
	}

	void VertexArray::AddBuffer(VertexBuffer* buffer, GLuint index)
	{
		Bind();
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