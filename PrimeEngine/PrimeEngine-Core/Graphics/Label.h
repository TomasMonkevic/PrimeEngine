#pragma once

#include <DllExport.h>
#include <Graphics/Font.h>
#include "Renderable.h"
#include <GameObject.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Label : public Renderable
	{
	private:

	public:
		//make private and use getters and setters
		const char* text;
		Font* font;

	public:
		Label(const char* _text, Font& _font);
		void Submit(Renderer2D* renderer) const override;

		Component* Copy() override;
	};
}}
