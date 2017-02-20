#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include <GL\glew.h>
#include "VertexBuffer.h"
#include <vector>

namespace PrimeEngine { namespace Graphics {

	class VertexArray
	{
	private:
		GLuint _Id;
		std::vector<VertexBuffer*> _buffers;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(VertexBuffer* buffer, GLuint index);
		void Bind() const;
		void Unbind() const;
	};
}}

#endif // !VERTEX_ARRAY