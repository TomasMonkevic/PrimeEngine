#ifndef PRIMEENGINE_WINDOW
#define PRIMEENGINE_WINDOW

#include <iostream> //probably not needed throwing exception would be better
//#define GLEW_STATIC
#include <GL/glew.h> //better use static?
#include <GLFW/glfw3.h>

#ifndef _DLL
#define MYLIBAPI __declspec(dllimport)
#else
#define MYLIBAPI __declspec(dllexport)
#endif

namespace PrimeEngine
{
	namespace Graphics
	{
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

		class MYLIBAPI Window
		{
		private:
			char* _title;
			int _width, _height;
			GLFWwindow* _window;
			//TODO: Implement singletone
			static Window* instance;
		private:
			//constructor
		public:
			Window(char* title, int width, int height);
			~Window();
			static void SetWindow(char* title, int width, int height);
			void Initialize();
			void Update() const;
			bool Closed() const;
			static Window* GetWindow() { return instance; };
		};
	}
}
#endif // !PRIMEENGINE_WINDOW