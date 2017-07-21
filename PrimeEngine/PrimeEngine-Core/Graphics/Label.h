#ifndef PRIME_LABEL
#define PRIME_LABEL

#include <DllExport.h>
#include <Graphics/Font.h>
#include <string>
#include "Renderable.h"
#include <GameObject.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Label : public Renderable
	{
	private:

	public:
		//make private and use getters and setters
		std::string text;
		Font* font;

	public:
		explicit Label(std::string& _text, Font& _font);
		void Submit(Renderer2D* renderer) const override;
	};
}}

#endif // !PRIME_LABEL
