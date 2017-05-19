#include "Label.h"

namespace PrimeEngine { namespace Graphics {

	Label::Label(const std::string& _text, const std::string& _fontName, const Math::Vector3& position, const Math::Vector4& color)
		: Renderable2D(position, Math::Vector2::one, NULL, color), text(_text), fontName(_fontName)
	{

	}

	void Label::Submit(Renderer2D* renderer) const
	{
		//renderer->DrawLabel(this);
	}
}}