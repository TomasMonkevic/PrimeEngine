#include "Label.h"

namespace PrimeEngine { namespace Graphics {

	Label::Label(const std::string& _text, Font& _font)
		: font(&_font), text(_text)
	{
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawLabel(text, GetGameObject()->GetTransform().GetPosition(), *font);
	}
}}