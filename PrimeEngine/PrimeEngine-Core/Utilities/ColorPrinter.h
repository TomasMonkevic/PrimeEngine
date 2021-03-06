#pragma once

#include "../Graphics/Color.h"

namespace PrimeEngine
{
    class PRIMEENGINEAPI ColorPrinter
    {
    public:
        static void Print(const PrimeEngine::Graphics::Color& color, const char* format, ...);
    };
}
