#ifndef SIMPLE_SPRITE_H
#define SIMPLE_SPRITE_H

#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexBuffer.h"
#include "Buffers\VertexArray.h"
#include "Color.h"
#include <Graphics\Shader\Shader.h>
#include "Renderable2D.h"
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI SimpleSprite : public Renderable2D
	{
	private:
		Shader& _shader;
		VertexArray* _vertexArray;
		IndexBuffer* _indexBuffer;
	public:
		SimpleSprite(const Math::Vector3& position, const Math::Vector2& size, const Color& color, Shader& shader);
		~SimpleSprite() override;

		inline const VertexArray* GetVertexArray() const
		{
			return _vertexArray;
		}

		inline Shader& GetShader() const
		{
			return _shader;
		}

		inline const IndexBuffer* GetIndexBuffer() const
		{
			return _indexBuffer;
		}
	};
}}

#endif // !SIMPLE_SPRITE_H