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
			virtual void Clear() = 0; //common code
			virtual bool IsReady() const = 0; //only on android
			virtual void Destroy() = 0;
			virtual bool IsClosed() const = 0; //only on desktop

			virtual void SetSize(int width, int height) = 0; //common code
			virtual Math::Vector2 GetSize() const = 0; //common code

			virtual void SetColor(const Color& color) = 0; //common code
			virtual const Color& GetColor() const = 0; //common code
		};

		// Factory functions for the various types of windows to abstract
		// over the platform-dependent implementations.
		BasicWindow* GetWindow();
	}
}