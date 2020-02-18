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

		public:
			virtual ~BasicWindow() {}
			
			virtual void Destroy();
			virtual void Initialize();
			virtual void Update() const;
			virtual void Clear() const;

			virtual void SetTitle(const char* title);
			void GetTitle();

			virtual void SetSize(const char* title, int width, int height);
			virtual Math::Vector2 GetSize() const;

			virtual void SetColor(const Color& color);
			virtual const Color& GetColor() const;
		};

		// Factory functions for the various types of windows to abstract
		// over the platform-dependent implementations.
		BasicWindow* GetWindow();
	}
}