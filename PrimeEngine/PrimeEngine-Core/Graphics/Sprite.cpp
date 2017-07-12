#include "Sprite.h"
#include "Renderer2D.h"

namespace PrimeEngine { namespace Graphics {

	Sprite::Sprite(const Math::Vector2& size, const Color& color) //might not be needed
		: Sprite(size, NULL, color)
	{

	}

	Sprite::Sprite(const Math::Vector2& size, Texture* texture, const Color& color)
		: _size(size), _texture(texture), _color(color)
	{
		SetTextureCords();
		if (!texture)
		{
			_color = Color::white;
		}
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::Submit(Renderer2D* renderer) const
	{
		renderer->Submit(this);
	}
}}