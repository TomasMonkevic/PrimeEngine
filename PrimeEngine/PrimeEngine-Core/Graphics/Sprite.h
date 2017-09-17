#ifndef SPRITE_H
#define SPRITE_H

#include <Math/Math.h>
#include "Color.h"
#include "Renderable.h"
#include "Texture.h"
#include <DllExport.h>
#include <Components\Component.h>

namespace PrimeEngine { namespace Graphics {

	//class Renderer2D;

	class PRIMEENGINEAPI Sprite : public Renderable
	{
	private:
		Math::Vector2 _size;
		Color _color;
		Math::Vector2 _textureCord[4];
		Texture* _texture;

	private:
		void SetTextureCords()
		{
			_textureCord[0] = Math::Vector2(0, 0);
			_textureCord[1] = Math::Vector2(1, 0);
			_textureCord[2] = Math::Vector2(1, 1);
			_textureCord[3] = Math::Vector2(0, 1);
		}

	public:
		explicit Sprite(const Math::Vector2& size, const Color& color);
		explicit Sprite(const Math::Vector2& size, const char* texturePath, const Color& color = Color(1.0f, 1.0f, 1.0f, 1.0f));
		Sprite(const Sprite& right);

		~Sprite() override;

		void Submit(Renderer2D* renderer) const override;

		inline const Texture& GetTexture() const { return *_texture; }

		inline const Math::Vector2& GetSize() const
		{
			return _size;
		}

		inline const Color& GetColor() const
		{
			return _color;
		}

		inline const Math::Vector2& GetTextureCords(unsigned index) const
		{
			return _textureCord[index];
		}

		inline const GLuint GetTextureId() const
		{
			return _texture ? _texture->GetId() : 0;
		}
	};
}}

#endif // !SPRITE_H