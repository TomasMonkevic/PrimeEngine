#pragma once

#include <DllExport.h>
#include <Graphics/OpenGL.h>
#include <Graphics/BasicWindow.h>
#include <EGL/egl.h>
#include <android/native_activity.h>

namespace PrimeEngine
{
	namespace Graphics
	{
		class PRIMEENGINEAPI AndroidWindow : public BasicWindow
		{
		private:
            EGLDisplay _display;
			EGLSurface _surface;
			EGLContext _context;
			ANativeWindow* _nativeWindow;
            ANativeActivity* _nativeActivity;
			Color _color = Color::White();
			int _width, _height;

		public:
			virtual ~AndroidWindow();

            void SetNativeAndroidWIndow(ANativeWindow* nativeWindow);
            void SetNativeAndroidActivity(ANativeActivity* nativeActivity);
            ANativeActivity* GetNativeActivity();

			// overridden from BasicWindow
			void Initialize() override;
			void Update() override;
			void Clear() override;
			bool IsReady() const override;
			void Destroy() override;
			bool IsClosed() const override;

			void SetSize(int width, int height) override;
			Math::Vector2 GetSize() const override;

			void SetColor(const Color& color) override;
			const Color& GetColor() const override;
		};
	}
}