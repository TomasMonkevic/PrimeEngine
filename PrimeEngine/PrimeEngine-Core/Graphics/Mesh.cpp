#include "Mesh.h"

namespace PrimeEngine { namespace Graphics {

	Mesh* Mesh::Cube(const Color& color, float width, float height, float depth)
	{
		//TODO not sure if the uv's are quit correct
		TempVertexData vertecies[] = {
			{ Vector3(-0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::down() },
			{ Vector3(-0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::left() },
			{ Vector3(-0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::forward() },
			{ Vector3(0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::down() },
			{ Vector3(0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::right() },
			{ Vector3(0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::forward() },
			{ Vector3(-0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::up() },
			{ Vector3(-0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::left() },
			{ Vector3(-0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::forward() },
			{ Vector3(0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::up() },
			{ Vector3(0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::right() },
			{ Vector3(0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::forward() },
			{ Vector3(-0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::up() },
			{ Vector3(-0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::left() },
			{ Vector3(-0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::back() },
			{ Vector3(0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::up() },
			{ Vector3(0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::right() },
			{ Vector3(0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::back() },
			{ Vector3(-0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::down() },
			{ Vector3(-0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::left() },
			{ Vector3(-0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::back() },
			{ Vector3(0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::down() },
			{ Vector3(0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::right() },
			{ Vector3(0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::back() }
		};
		for (auto& vertex : vertecies)
		{
			vertex.position.x *= width;
			vertex.position.y *= height;
			vertex.position.z *= depth;
		}
		static GLushort indecies[] = {
			0 * 3 + 2, 1 * 3 + 2, 2 * 3 + 2,
			2 * 3 + 2, 1 * 3 + 2, 3 * 3 + 2,

			2 * 3 + 0, 3 * 3 + 0, 4 * 3 + 0,
			4 * 3 + 0, 3 * 3 + 0, 5 * 3 + 0,

			4 * 3 + 2, 5 * 3 + 2, 6 * 3 + 2,
			6 * 3 + 2, 5 * 3 + 2, 7 * 3 + 2,

			6 * 3 + 0, 7 * 3 + 0, 0 * 3 + 0,
			0 * 3 + 0, 7 * 3 + 0, 1 * 3 + 0,

			1 * 3 + 1, 7 * 3 + 1, 3 * 3 + 1,
			3 * 3 + 1, 7 * 3 + 1, 5 * 3 + 1,

			6 * 3 + 1, 0 * 3 + 1, 4 * 3 + 1,
			4 * 3 + 1, 0 * 3 + 1, 2 * 3 + 1
		};
		Mesh* cube = new Mesh(vertecies, sizeof(TempVertexData) * 24, indecies, 36);
		return cube;
	}

	Mesh::Mesh(const void* vertecies, unsigned size, const GLushort* indecies, unsigned indeciesCount)
	{
		_vbo = new VertexBuffer(vertecies, size, GL_STATIC_DRAW);
		_vbo->Bind();

		_vao = new VertexArray();
		_vao->Bind();


		_vao->AddAttribute(0, 3, GL_FLOAT, false, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::position)));
		_vao->AddAttribute(1, 4, GL_UNSIGNED_BYTE, true, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::color32)));
		_vao->AddAttribute(2, 3, GL_FLOAT, false, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::normal)));
		_vao->AddAttribute(3, 2, GL_FLOAT, false, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::uv)));


		_vbo->Unbind();
		_vao->Unbind();

		_ibo = new IndexBuffer(indecies, indeciesCount);
	}

	Mesh::~Mesh()
	{
		delete _vbo;
		delete _ibo;
		delete _vao;
	}

	void Mesh::Bind()
	{
		_vao->Bind();
		_ibo->Bind();
	}

	void Mesh::Unbind()
	{
		_ibo->Unbind();
		_vao->Unbind();
	}
}}