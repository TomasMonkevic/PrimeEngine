#include "VertexArray.h"

namespace PrimeEngine { namespace Graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &_Id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &_Id);
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