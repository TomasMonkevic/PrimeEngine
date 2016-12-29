#include "Window.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		Window* Window::instance = NULL;

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			std::cout << key << std::endl;
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Window::Window(char* title, int width, int height)
		{
			_title = title;
			_width = width;
			_height = height;
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::SetWindow(char* title, int width, int height)
		{
			if (!instance)
			{
				instance = new Window(title, width, height);
			}
		}

		void Window::Initialize()
		{
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
			if (!_window)
			{
				throw "Failed to create GLFW window";
				glfwTerminate();
			}
			glfwMakeContextCurrent(_window);
			glfwSetKeyCallback(_window, key_callback);

			// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				throw "Failed to initialize GLEW";
			}
			glViewport(0, 0, _width, _height);
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(_window) == 1;
		}

		void Window::Update() const
		{
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(_window);
		}
	}
}