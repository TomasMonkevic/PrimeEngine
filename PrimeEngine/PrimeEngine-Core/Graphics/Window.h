#pragma once

#ifdef PE_ANDROID
	#include <GLES3/gl31.h>
	#include <EGL/egl.h>
    #include <android/native_activity.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif
#include "Color.h"
#include "../Math/Vector4.h"
#include "../Math/Vector2.h"
#include "../DllExport.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		class PRIMEENGINEAPI Window
		{
			#ifndef PE_ANDROID
			friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
			#endif
		private:
			const char* _title;
			int _width, _height;
			#ifdef PE_ANDROID
			EGLDisplay _display;
			EGLSurface _surface;
			EGLContext _context;
			ANativeWindow* _nativeWindow;
            ANativeActivity* _nativeActivity;
            #else
			GLFWwindow* _window;
			#endif
			static Window* instance;
			bool _isFullScreen;
			Color _color = Color::White();
		private:
			Window(const char* title, int width, int height);
			Window(const char* title);
			~Window();
			void isInstanceCreated();
		public:
			static void SetWindow(const char* title);
			static void SetWindow(const char* title, int width, int height);

			inline static Window* GetWindow() 
			{ 
				return instance; 
			}

			inline void SetColor(const Color& color)
			{
				isInstanceCreated();
				_color = color;
			}

			inline const Color& GetColor() const
			{
				return _color;
			}

			inline bool IsReady() const
            {
            #ifdef PE_ANDROID
                return _display;
            #else
                return true;
            #endif
            }

#ifdef PE_ANDROID
            inline void SetNativeAndroidWIndow(ANativeWindow* nativeWindow)
			{
				_nativeWindow = nativeWindow;
			}

            inline void SetNativeAndroidActivity(ANativeActivity* nativeActivity)
            {
                _nativeActivity = nativeActivity;
            }

            ANativeActivity* GetNativeActivity() {
			    return _nativeActivity;
			}
#endif

			inline Math::Vector2 GetSize() const
			{
				glViewport(0, 0, _width, _height);
				return Math::Vector2((float)_width, (float)_height);
			}

			inline void EnableVSync(bool isEnabled)
			{
				#ifndef PE_ANDROID
				glfwSwapInterval((GLint)isEnabled);
				#endif
			}

			void Close() const;
			void Destroy();
			void Initialize();
			void Update() const;
			bool Closed() const;
			void Clear() const;
		};
	}
}