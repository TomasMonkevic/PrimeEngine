#ifndef RENDERABLE2D
#define RENDERABLE2D

#include <GL\glew.h>
#include "..\Core\Math.h"
#include "Renderer2D.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Renderable2D //might need to seperate translation component from renderable
	{
	protected:
		Math::Vector3 _position;
		Math::Matrix4x4 _rotationMatrix = Math::Matrix4x4::identity; //change to quaternion
		Math::Vector3 _scale = Math::Vector3::one;

		Math::Vector2 _size;
		Math::Vector4 _color;
	public:
		Renderable2D(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color)
			: _position(position), _size(size), _color(color)
		{

		}

		virtual ~Renderable2D()
		{

		}

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		void Rotate(float angle, const Math::Vector3& axis) //change to quaternion
		{
			_rotationMatrix *= Math::Matrix4x4::Rotate(angle, axis);
		}

		inline void SetPosition(const Math::Vector3& position)
		{
			_position = position;
		}

		inline void SetScale(const Math::Vector3& scale)
		{
			_scale = scale;
		}

		inline Math::Matrix4x4 GetModelMatrix() const
		{
			return Math::Matrix4x4::TRS(_position, _rotationMatrix, _scale);
		}

		inline const Math::Vector3& GetPosition() const
		{
			return _position;
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