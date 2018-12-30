#pragma once

#include <DllExport.h>
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/VertexArray.h"
#include "../Math/Math.h"
#include "Color.h"


namespace PrimeEngine { namespace Graphics {

	using namespace PrimeEngine::Math;

	struct TempVertexData
	{
		Vector3 position;
		unsigned color32;
		Vector2 uv;
		Vector3 normal;
		Vector3 tangent;
	};

	class PRIMEENGINEAPI Mesh
	{
	private:
		VertexBuffer* _vbo;
		IndexBuffer* _ibo;
		VertexArray* _vao;

	public:
		//TODO shoul color be here?
		static Mesh* Cube(const Color& color = Color::White(), float width = 1.0f, float height = 1.0f, float depth = 1.0f);

		Mesh(const void* vertecies, unsigned size, const GLushort* indecies, unsigned indeciesCount);
		~Mesh();

		void Bind();
		void Unbind();

		unsigned GetIndexCount() const { return _ibo->GetCount(); }
	};
}}