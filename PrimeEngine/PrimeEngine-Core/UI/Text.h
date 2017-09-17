#pragma once

#include <DllExport.h>
#include "UIObject.h"
#include <Graphics\Label.h>

namespace PrimeEngine { namespace UI {

	class PRIMEENGINEAPI Text : public UIObject
	{
	public:
		explicit Text(Graphics::Font& font);
		Text(const char* text, Graphics::Font& font);
		~Text() override;
	};
}}
