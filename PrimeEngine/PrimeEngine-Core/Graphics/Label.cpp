#include "Label.h"

namespace PrimeEngine { namespace Graphics {

	Label::Label(const char* _text, Font& _font)
		: font(&_font), text(_text)
	{
		AddType<Label>();
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawLabel(text, GetGameObject()->GetTransform().Position, *font);
	}
}}