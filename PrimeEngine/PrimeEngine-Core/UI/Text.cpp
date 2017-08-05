#include "Text.h"

namespace PrimeEngine { namespace UI {

	Text::Text(Graphics::Font& font)
		: Text("", font)
	{

	}

	Text::Text(const std::string& text, Graphics::Font& font)
	{
		_gameObject->AddComponent(new Graphics::Label(text, font));
	}

	Text::~Text()
	{

	}
}}