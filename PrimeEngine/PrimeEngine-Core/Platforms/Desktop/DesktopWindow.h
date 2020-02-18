#pragma once

#include <Graphics/OpenGL.h>
#include <GLFW/glfw3.h>
#include "Color.h"
#include <Graphics/BasicWindow.h>
#include "../Math/Vector4.h"
#include "../Math/Vector2.h"
#include "../DllExport.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		class PRIMEENGINEAPI DesktopWindow : public BasicWindow
		{
		private:
			const char* _title = "PrimeEngine";
			Color _color = Color::White();
			int _width, _height;
			GLFWwindow* _window;
			bool _isFullScreen;

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