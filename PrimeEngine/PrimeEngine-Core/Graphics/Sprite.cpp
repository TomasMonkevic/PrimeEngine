#include "Sprite.h"

namespace PrimeEngine { namespace Graphics {

	Sprite::Sprite(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color) //might not be needed
		: Renderable2D(position, size, NULL, color)
	{

	}

	Sprite::Sprite(const Math::Vector3& position, const Math::Vector2& size, Texture* texture, const Math::Vector4& color)
		: Renderable2D(position, size, texture, color)
	{
		if (!texture)
		{
			_color = Math::Vector4(1, 1, 1, 1);
		}
	}

	Sprite::~Sprite()
	{

	}
}}