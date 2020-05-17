#include "VertexArray.h"

namespace PrimeEngine { namespace Graphics {

	VertexArray::VertexArray()
	{
		GlCall(glGenVertexArrays(1, &_Id));
	}

	VertexArray::~VertexArray()
	{
		GlCall(glDeleteVertexArrays(1, &_Id));
	}

	void VertexArray::Bind() const
	{
		GlCall(glBindVertexArray(_Id));
	}

	void VertexArray::Unbind() const
	{
		GlCall(glEnableVertexAttribArray(0));
	}

}}