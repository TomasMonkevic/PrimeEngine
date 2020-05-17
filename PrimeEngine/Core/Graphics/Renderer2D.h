#pragma once

#include <vector>
#include <Graphics/Font.h>
#include <Math/Math.h>
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class Sprite;
	class Label;

	class PRIMEENGINEAPI Renderer2D
	{
	protected:
		Renderer2D() {}

	public:
		virtual ~Renderer2D() {}

		virtual void Begin() {}
		virtual void Submit(const Sprite* renderable2D) = 0;
		virtual void DrawLabel(const Label& textComponent) = 0;
		virtual void End() {}
		virtual void Flush() = 0;
	};
}}