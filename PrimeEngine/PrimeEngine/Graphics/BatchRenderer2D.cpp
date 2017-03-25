#include "BatchRenderer2D.h"

namespace PrimeEngine { namespace Graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		_indexCount = 0;
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_POSITION_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, NULL);
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLushort* indecies = new GLushort[RENDERER_INDECIES_SIZE];
		int offset = 0;
		for (size_t i = 0; i < RENDERER_INDECIES_SIZE; i+=6)
		{
			indecies[i] = offset;
			indecies[i + 1] = offset + 1;
			indecies[i + 2] = offset + 2;
			indecies[i + 3] = offset + 2;
			indecies[i + 4] = offset + 3;
			indecies[i + 5] = offset;
			offset += 4;
		}
		_ibo = new IndexBuffer(indecies, RENDERER_INDECIES_SIZE);
		delete[] indecies;
		glBindVertexArray(0);
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete _ibo;
		glDeleteBuffers(1, &_vbo);
	}

	void BatchRenderer2D::Begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::Submit(const Renderable2D* renderable2D)
	{
		const Math::Vector4& color = renderable2D->GetColor();
		const Math::Vector2& size = renderable2D->GetSize();

		_buffer->position = *_transformationStackBack * renderable2D->GetModelMatrix() * Math::Vector3(-size.x / 2.0f, size.y / 2.0f, 0);
		_buffer->color = color;
		_buffer++;

		_buffer->position = *_transformationStackBack * renderable2D->GetModelMatrix() * Math::Vector3(size.x / 2.0f,  size.y / 2.0f, 0);
		_buffer->color = color;
		_buffer++;

		_buffer->position = *_transformationStackBack * renderable2D->GetModelMatrix() * Math::Vector3(size.x / 2.0f, -size.y / 2.0f, 0);
		_buffer->color = color;
		_buffer++;

		_buffer->position = *_transformationStackBack * renderable2D->GetModelMatrix() * Math::Vector3(-size.x / 2.0f, -size.y / 2.0f, 0);
		_buffer->color = color;
		_buffer++;

		_indexCount += 6;
	}

	void BatchRenderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::Flush()
	{
		glBindVertexArray(_vao);
		_ibo->Bind();
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, NULL);
		_ibo->Unbind();
		glBindVertexArray(0);
		_indexCount = 0;
	}
}}