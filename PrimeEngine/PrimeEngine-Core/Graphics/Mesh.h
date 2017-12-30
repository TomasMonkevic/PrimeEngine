#pragma once

#include <DllExport.h>
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexBuffer.h"
#include "Buffers\VertexArray.h"
#include "../Math/Math.h"


namespace PrimeEngine { namespace Graphics {

	using namespace PrimeEngine::Math;

	struct TempVertexData
	{
		Vector3 position;
		unsigned color32;
	};

	class PRIMEENGINEAPI Mesh
	{
	private:
		VertexBuffer* _vbo;
		IndexBuffer* _ibo;
		VertexArray* _vao;

	public:
		static Mesh* Cube();

		Mesh(const void* vertecies, unsigned size, const GLushort* indecies, unsigned indeciesCount);
		~Mesh();

		void Bind();
		void Unbind();

		unsigned GetIndexCount() const { return _ibo->GetCount(); }
	};
}}