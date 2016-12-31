#ifndef PRIMEENGINE_WINDOW
#define PRIMEENGINE_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DllExport.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		class PRIMEENGINEAPI Window
		{
		private:
			char* _title;
			int _width, _height;
			GLFWwindow* _window;
			static Window* instance;
			bool _isFullScreen;
		private:
			Window(char* title, int width, int height);
			Window(char* title);
			~Window();
		public:
			static void SetWindow(char* title);
			static void SetWindow(char* title, int width, int height);
			static Window* GetWindow() { return instance; };
			void Close() const;
			void Destroy() const;
			void Initialize();
			void Update() const;
			bool Closed() const;
		};
	}
}
#endif // !PRIMEENGINE_WINDOW