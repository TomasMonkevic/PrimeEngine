#ifndef SPRITE_H
#define SPRITE_H

#include "Renderable2D.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Sprite : public Renderable2D
	{
	private:

	public:
		Sprite(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color);
		Sprite(const Math::Vector3& position, const Math::Vector2& size, Texture* texture, const Math::Vector4& color = Math::Vector4(1, 1, 1, 0));
		~Sprite() override;
	};
}}

#endif // !SPRITE_H