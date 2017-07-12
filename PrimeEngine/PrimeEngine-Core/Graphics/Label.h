#ifndef PRIME_LABEL
#define PRIME_LABEL

#include <DllExport.h>
#include <Graphics/Font.h>
#include <string>

namespace PrimeEngine { namespace Graphics {

	//don't inherit from renderable. inherit from gameObject or even better from UI element
	class PRIMEENGINEAPI Label
	{
	private:

	public:
		std::string text;
		Font* font;

	public:
		Label(std::string& _text, const Math::Vector3& position, Font& _font);
		//void Submit(Renderer2D* renderer) const;
	};
}}

#endif // !PRIME_LABEL
