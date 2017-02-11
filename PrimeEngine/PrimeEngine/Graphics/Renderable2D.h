#ifndef RENDERABLE2D
#define RENDERABLE2D

#include <GL\glew.h>
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexBuffer.h"
#include "Buffers\VertexArray.h"
#include "Shader.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Renderable2D
	{
	protected:
		Math::Vector3 _position;
		Math::Matrix4x4 _rotationMatrix = Math::Matrix4x4::identity; //change to quaternion
		Math::Vector3 _scale = Math::Vector3::one;

		Math::Vector2 _size;
		Math::Vector4 _color;

		Shader& _shader;
		VertexArray* _vertexArray;
		IndexBuffer* _indexBuffer;
	public:
		Renderable2D(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color, Shader& shader)
			: _position(position), _size(size), _color(color), _shader(shader)
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

		void Rotate(float angle, const Math::Vector3& axis) //change to quaternion
		{
			_rotationMatrix *= Math::Matrix4x4::Rotate(angle, axis);
		}

		inline Math::Matrix4x4 GetModelMatrix() const
		{
			return Math::Matrix4x4::TRS(_position, _rotationMatrix, _scale);
			//return _modelMatrix;
		}

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

		inline const Math::Vector3& GetPosition() const
		{
			return _position;
		}

		inline void SetPosition(const Math::Vector3& position)
		{
			_position = position;
		}

		inline void SetScale(const Math::Vector3& scale)
		{
			_scale = scale;
		}

		inline const Math::Vector2& GetSize() const
		{
			return _size;
		}

		inline const Math::Vector4& GetColor() const
		{
			return _color;
		}
	};
}}

#endif // !RENDERABLE2D