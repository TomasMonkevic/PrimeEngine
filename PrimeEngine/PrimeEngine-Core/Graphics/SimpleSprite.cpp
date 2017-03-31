#include "SimpleSprite.h"

namespace PrimeEngine { namespace Graphics {

	SimpleSprite::SimpleSprite(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color, Shader& shader)
		: Renderable2D(position, size, color), _shader(shader)
	{
		_vertexArray = new VertexArray();

		GLfloat vertices[] = { //position.z???
			-size.x / 2, -size.y / 2, 0,
			-size.x / 2,  size.y / 2, 0,
			 size.x / 2,  size.y / 2, 0,
			 size.x / 2, -size.y / 2, 0
		};

		GLfloat colors[] = {
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		GLushort indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		_vertexArray->AddBuffer(new VertexBuffer(vertices, 4 * 3, 3), 0);
		_vertexArray->AddBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);
		_indexBuffer = new IndexBuffer(indices, 6);
	}

	SimpleSprite::~SimpleSprite()
	{
		delete _vertexArray;
		_vertexArray = NULL;
		delete _indexBuffer;
		_indexBuffer = NULL;
	}
}}