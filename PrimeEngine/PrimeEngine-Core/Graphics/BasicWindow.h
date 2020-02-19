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
			// TODO move common variables and implement common functions here

		public:
			virtual ~BasicWindow() {}
			
			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Clear() = 0;
			virtual bool IsReady() const = 0; //is this needed here???
			virtual void Destroy() = 0;
			virtual bool IsClosed() const = 0; //is this needed here???

			virtual void SetTitle(const char* title) = 0;
			virtual const char* GetTitle() const = 0;

			virtual void SetSize(int width, int height) = 0;
			virtual Math::Vector2 GetSize() const = 0;

			virtual void SetColor(const Color& color) = 0;
			virtual const Color& GetColor() const = 0;
		};

		// Factory functions for the various types of windows to abstract
		// over the platform-dependent implementations.
		BasicWindow* GetWindow();
	}
}