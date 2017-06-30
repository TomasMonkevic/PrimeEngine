#include "Sprite.h"

namespace PrimeEngine { namespace Graphics {

	Sprite::Sprite(const Math::Vector3& position, const Math::Vector2& size, const Color& color) //might not be needed
		: Renderable2D(position, size, NULL, color)
	{

	}

	Sprite::Sprite(const Math::Vector3& position, const Math::Vector2& size, Texture* texture, const Color& color)
		: Renderable2D(position, size, texture, color)
	{
		if (!texture)
		{
			_color = Color::white;
		}
	}

	Sprite::~Sprite()
	{

	}
}}