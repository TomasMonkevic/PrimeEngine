#include "Label.h"

namespace PrimeEngine { namespace Graphics {

	Label::Label(std::string& _text, Font& _font)
		: font(&_font), text(_text)
	{
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		//the position here should be global not local
		renderer->DrawLabel(text, Math::Vector3::zero, *font);
	}
}}