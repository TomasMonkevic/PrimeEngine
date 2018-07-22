#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
			friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		private:
			const char* _title;
			int _width, _height;
			GLFWwindow* _window;
			static Window* instance;
			bool _isFullScreen;
			Color _color = Color::white;
		private:
			Window(const char* title, int width, int height);
			Window(const char* title);
			~Window();
			inline void isInstanceCreated();
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
				return Math::Vector2((float)_width, (float)_height);
			}

			inline void EnableVSync(bool isEnabled)
			{
				glfwSwapInterval((GLint)isEnabled);
			}

			void Close() const;
			void Destroy() const;
			void Initialize();
			void Update() const;
			bool Closed() const;
			void Clear() const;
		};
	}
}