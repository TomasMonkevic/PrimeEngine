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
		explicit Color(float r, float g, float b, float a = 1.0f);
		explicit Color(int r, int g, int b, int a = 255);
		explicit Color(unsigned int hex);

		const unsigned ToColor32() const;
		inline const float& operator[](unsigned index) const
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
				//error
				return _r;
			}
		}

		inline float& operator[](unsigned index)
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
				//error
				return _r;
			}
		}
	};
}}