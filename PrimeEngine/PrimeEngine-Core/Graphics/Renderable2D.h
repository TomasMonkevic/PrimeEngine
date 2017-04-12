#ifndef PRIME_RENDERABLE2D
#define PRIME_RENDERABLE2D

#include <GL\glew.h>
#include "..\Core\Math.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	struct VertexData
	{
		Math::Vector3 position;
		Math::Vector4 color;
		Math::Vector2 textureCord;
		float texture;
	};

	class PRIMEENGINEAPI Renderable2D //might need to seperate translation component from renderable
	{
	protected:
		Math::Vector3 _position;
		Math::Matrix4x4 _rotationMatrix = Math::Matrix4x4::identity; //change to quaternion
		Math::Vector3 _scale = Math::Vector3::one;

		Math::Vector2 _size;
		Math::Vector4 _color = Math::Vector4::one;
		Math::Vector2 _textureCord[4];
		Texture* _texture;

	private:
		void SetTextureCords()
		{
			_textureCord[0] = Math::Vector2(0, 1);
			_textureCord[1] = Math::Vector2(1, 1);
			_textureCord[2] = Math::Vector2(1, 0);
			_textureCord[3] = Math::Vector2(0, 0);
		}

	public:
		Renderable2D(const Math::Vector3& position, const Math::Vector2& size, Texture* texture, const Math::Vector4& color) //change the same as sprite constructor
			: _position(position), _size(size), _texture(texture), _color(color)
		{
			SetTextureCords();
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

		inline const Math::Matrix4x4 GetModelMatrix() const
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

		inline const Math::Vector2& GetTextureCords(unsigned index) const
		{
			return _textureCord[index];
		}

		inline const GLuint GetTextureId() const
		{
			return _texture == NULL ? 0 : _texture->GetId();
		}
	};
}}

#endif // !PRIME_RENDERABLE2D