#include "Label.h"

namespace PrimeEngine { namespace Graphics {

	Label::Label(std::string _text, Font& _font)
		: text(_text), font(&_font)
	{
		AddType<Label>();
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawLabel(*this);
	}

	Component* Label::Copy()
	{
		return (new Label(*this));
	}
}}