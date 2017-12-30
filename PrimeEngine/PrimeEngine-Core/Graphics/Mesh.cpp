#include "Mesh.h"

namespace PrimeEngine { namespace Graphics {

	Mesh* Mesh::Cube()
	{
		static TempVertexData vertecies[] = {
			{ Vector3(-0.500000, -0.500000,  0.500000), 0xff0000ff },
			{ Vector3(0.500000, -0.500000,  0.500000), 0xff0000ff },
			{ Vector3(-0.500000,  0.500000,  0.500000), 0xff0000ff },
			{ Vector3(0.500000,  0.500000,  0.500000), 0xff0000ff },
			{ Vector3(-0.500000,  0.500000, -0.500000), 0xffffffff },
			{ Vector3(0.500000,  0.500000, -0.500000), 0xffffffff },
			{ Vector3(-0.500000, -0.500000, -0.500000), 0xffffffff },
			{ Vector3(0.500000, -0.500000, -0.500000), 0xffffffff }
		};
		static GLushort indecies[] = {
			0, 1, 2,
			2, 1, 3,

			2, 3, 4,
			4, 3, 5,

			4, 5, 6,
			6, 5, 7,

			6, 7, 0,
			0, 7, 1,

			1, 7, 3,
			3, 7, 5,

			6, 0, 4,
			4, 0, 2
		};
		Mesh* cube = new Mesh(vertecies, sizeof(TempVertexData) * 8, indecies, 36);
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