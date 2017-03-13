#ifndef PRIMEENGINE_WINDOW
#define PRIMEENGINE_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
			Math::Vector4 _color = Math::Vector4::one;
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

			inline void SetColor(const Math::Vector4& color)
			{
				isInstanceCreated();
				_color = color;
			}

			inline const Math::Vector4& GetColor() const
			{
				return _color;
			}

			inline Math::Vector2 GetSize() const
			{
				return Math::Vector2((float)_width, (float)_height);
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
#endif // !PRIMEENGINE_WINDOW