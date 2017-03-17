#include "Sprite.h"


namespace PrimeEngine { namespace Graphics {

	Sprite::Sprite(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color)
		: Renderable2D(position, size, color)
	{

	}

	Sprite::~Sprite()
	{

	}
}}