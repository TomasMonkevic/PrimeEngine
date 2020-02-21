#pragma once

#include <DllExport.h>
#include <Graphics/Font.h>
#include "Renderable.h"
#include <GameObject.h>

namespace PrimeEngine { namespace Graphics {

	//TODO later rename to Text or TextBox and move to components
	class PRIMEENGINEAPI Label : public Renderable
	{
	private:

	public:
		//TODO make private and use getters and setters
		std::string text;
		Font* font;

	public:
		Label(std::string _text, Font& _font);
		void Submit(Renderer2D* renderer) const override;

		Component* Copy() override;
	};
}}
