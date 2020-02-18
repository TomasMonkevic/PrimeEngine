#pragma once

#include <DllExport.h>

namespace PrimeEngine
{
	namespace Graphics
	{
		// This is an abstarct class for all Window clases
		// Check DesktopWindow and AndroidWindow for more details
		class PRIMEENGINEAPI BasicWindow
		{
		protected:
			// TODO move common variables and implement common functions here
			virtual ~BasicWindow() {}

		public:
			virtual void SetTitle(const char* title);
			virtual void SetSize(const char* title, int width, int height);
			virtual void SetColor(const Color& color);
			virtual const Color& GetColor() const;
			virtual Math::Vector2 GetSize() const;
			virtual void Close() const;
			virtual void Destroy();
			virtual void Initialize();
			virtual void Update() const;
			virtual bool Closed() const;
			virtual void Clear() const;
		};

		// Factory functions for the various types of windows to abstract
		// over the platform-dependent implementations.
		BasicWindow* GetWindow();
	}
}