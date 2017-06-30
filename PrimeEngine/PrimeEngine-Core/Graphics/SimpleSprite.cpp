#include "SimpleSprite.h"

namespace PrimeEngine { namespace Graphics {

	SimpleSprite::SimpleSprite(const Math::Vector3& position, const Math::Vector2& size, const Color& color, Shader& shader)
		: Renderable2D(position, size, NULL, color), _shader(shader)
	{
		_vertexArray = new VertexArray();

		GLfloat vertices[] = { //position.z???
			-size.x / 2, -size.y / 2, 0,
			-size.x / 2,  size.y / 2, 0,
			 size.x / 2,  size.y / 2, 0,
			 size.x / 2, -size.y / 2, 0
		};

		GLfloat colors[] = {
			color[0], color[1], color[2], color[3],
			color[0], color[1], color[2], color[3],
			color[0], color[1], color[2], color[3],
			color[0], color[1], color[2], color[3]
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