#pragma once

#include <DllExport.h>
#include "UIObject.h"
#include <Graphics\Label.h>

namespace PrimeEngine { namespace UI {

	class PRIMEENGINEAPI Text : public UIObject
	{
	public:
		explicit Text(Graphics::Font& font);
		explicit Text(const std::string& text, Graphics::Font& font);
		~Text() override;
	};
}}
