#ifndef PRIME_LABEL
#define PRIME_LABEL

#include <DllExport.h>
#include <Graphics/Font.h>
#include <string>
#include "Renderer2D.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Label
	{
	private:

	public:
		//make private and use getters and setters
		std::string text;
		Font* font;

	public:
		Label(std::string& _text, Font& _font);
		void Submit(Renderer2D* renderer) const;
	};
}}

#endif // !PRIME_LABEL
