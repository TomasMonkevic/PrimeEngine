#ifndef PRIME_LABEL
#define PRIME_LABEL

#include <DllExport.h>
#include <Graphics/Renderable2D.h>
#include <string>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Label : public Renderable2D
	{
	private:

	public:
		std::string text;
		std::string fontName;

	public:
		Label(const std::string& _text, const std::string& _fontName, const Math::Vector3& position, const Math::Vector4& color);
		void Submit(Renderer2D* renderer) const override;
	};
}}

#endif // !PRIME_LABEL
