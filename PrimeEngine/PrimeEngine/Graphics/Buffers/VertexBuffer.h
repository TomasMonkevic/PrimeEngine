#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <GL\glew.h>

namespace PrimeEngine { namespace Graphics {

	class VertexBuffer
	{
	private:
		GLuint _index;
		GLuint _componentCount;
	public:
		VertexBuffer(const GLfloat* data, GLsizei count, GLuint componentCount);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		inline GLuint GetComponentCount() const
		{
			return _componentCount;
		}
	};

}}

#endif // !VERTEX_BUFFER