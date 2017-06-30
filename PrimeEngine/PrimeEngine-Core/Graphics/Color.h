#pragma once

#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {
	
	class PRIMEENGINEAPI Color
	{
	private:
		float _r, _g, _b, _a;
	public:
		static const Color white;
		static const Color black;

	public:
		Color(float r, float g, float b, float a = 1.0f);
		Color(unsigned r, unsigned g, unsigned b, unsigned a = 255);
		Color(const char* hexColor);

		const unsigned ToColor32() const;
		inline const float operator[](unsigned index) const
		{
			switch (index)
			{
			case 0:
				return _r;
			case 1:
				return _g;
			case 2:
				return _b;
			case 3:
				return _a;
			default:
				return -1;
			}
		}
	};
}}