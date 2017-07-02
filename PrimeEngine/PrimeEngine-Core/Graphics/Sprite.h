#ifndef SPRITE_H
#define SPRITE_H

#include "Renderable2D.h"
#include "Color.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Sprite : public Renderable2D
	{
	private:

	public:
		Sprite(const Math::Vector3& position, const Math::Vector2& size, const Color& color);
		Sprite(const Math::Vector3& position, const Math::Vector2& size, Texture* texture, const Color& color = Color(1.0f, 1.0f, 1.0f, 1.0f));
		~Sprite() override;
	};
}}

#endif // !SPRITE_H