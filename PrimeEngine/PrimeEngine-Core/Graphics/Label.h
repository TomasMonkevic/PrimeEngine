#ifndef PRIME_LABEL
#define PRIME_LABEL

#include <DllExport.h>
#include <Graphics/Renderable2D.h>
#include <Graphics/Font.h>
#include <string>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Label : public Renderable2D
	{
	private:

	public:
		std::string text;
		Font* font;

	public:
		Label(std::string& _text, const Math::Vector3& position, Font& _font);
		void Submit(Renderer2D* renderer) const override;
	};
}}

#endif // !PRIME_LABEL
