#pragma once

#include <DllExport.h>
#include <Graphics/Color.h>
#include <Graphics/BasicWindow.h>
#include <Math/Vector4.h>
#include <Math/Vector2.h>

namespace PrimeEngine
{
	namespace Graphics
	{
		// This is an abstarct class for all Window clases
		// Check DesktopWindow and AndroidWindow for more details
		class PRIMEENGINEAPI BasicWindow
		{
		protected:
			Color _color = Color::White();
			int _width, _height;

		public:
			virtual ~BasicWindow() {}

			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Clear();
			virtual bool IsReady() const = 0;
			virtual void Destroy() = 0;
			virtual bool IsClosed() const = 0;

			virtual void SetSize(int width, int height);
			virtual Math::Vector2 GetSize() const;

			virtual void SetColor(const Color& color);
			virtual const Color& GetColor() const;
		};

		// Factory functions for the various types of windows to abstract
		// over the platform-dependent implementations.
		BasicWindow* GetWindow();
	}
}