#include "Label.h"

namespace PrimeEngine { namespace Graphics {

	Label::Label(std::string& _text, const Math::Vector3& position, Font& _font)
		: Renderable2D(position, Math::Vector2::one, NULL, Color::white), text(_text)
	{
		font = &_font;
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawLabel(text, _position, *font);
	}
}}