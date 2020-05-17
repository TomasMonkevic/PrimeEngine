#include "Mesh.h"

#ifdef BROKEN_OFFSETOF_MACRO
#undef offsetof
#define offsetof(type, member)   ((size_t)((char *)&(*(type *)0).member - \
                                           (char *)&(*(type *)0)))
#endif /* BROKEN_OFFSETOF_MACRO */

namespace PrimeEngine { namespace Graphics {

	Mesh* Mesh::Cube(const Color& color, float width, float height, float depth)
	{
		TempVertexData vertecies[] = {
			{ Vector3(-0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::down() },
			{ Vector3(-0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::left() },
			{ Vector3(-0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::forward() },
			{ Vector3(0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::down() },
			{ Vector3(0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::right() },
			{ Vector3(0.500000, -0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::forward() },
			{ Vector3(-0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::up() },
			{ Vector3(-0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::left() },
			{ Vector3(-0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::forward() },
			{ Vector3(0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::up() },
			{ Vector3(0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::right() },
			{ Vector3(0.500000,  0.500000,  0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::forward() },
			{ Vector3(-0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::up() },
			{ Vector3(-0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::left() },
			{ Vector3(-0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::back() },
			{ Vector3(0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::up() },
			{ Vector3(0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 0.0f), Vector3::right() },
			{ Vector3(0.500000,  0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 0.0f), Vector3::back() },
			{ Vector3(-0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::down() },
			{ Vector3(-0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::left() },
			{ Vector3(-0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::back() },
			{ Vector3(0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(1.0f, 1.0f), Vector3::down() },
			{ Vector3(0.500000, -0.500000, -0.500000),	color.ToColor32(), Vector2(0.0f, 1.0f), Vector3::right() },
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
		//calc tangents
		for (int i=0; i<sizeof(indecies)/sizeof(indecies[0]); i+=3)
		{
			Vector3 edge1 = vertecies[indecies[i + 1]].position - vertecies[indecies[i + 0]].position;
			Vector3 edge2 = vertecies[indecies[i + 2]].position - vertecies[indecies[i + 0]].position;
			Vector2 deltaUV1 = vertecies[indecies[i + 1]].uv - vertecies[indecies[i + 0]].uv;
			Vector2 deltaUV2 = vertecies[indecies[i + 2]].uv - vertecies[indecies[i + 0]].uv;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			Vector3 tangent(deltaUV2.y * edge1.x - deltaUV1.y * edge2.x, deltaUV2.y * edge1.y - deltaUV1.y * edge2.y, deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			tangent *= f;
			tangent.Normalized();

			vertecies[indecies[i + 0]].tangent = tangent;
			vertecies[indecies[i + 1]].tangent = tangent;
			vertecies[indecies[i + 2]].tangent = tangent;
		}
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
		_vao->AddAttribute(4, 3, GL_FLOAT, false, sizeof(TempVertexData), (const GLvoid*)(offsetof(TempVertexData, TempVertexData::tangent)));



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