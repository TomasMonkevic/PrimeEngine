#include "Window.h"
#include "../Input.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		Window* Window::instance = NULL;

		Window::Window(const char* title, int width, int height) : 
			_title(title), _width(width), _height(height)
		{
			_isFullScreen = false;
		}

		Window::Window(const char* title) : _title(title)
		{
			_isFullScreen = true;
		}

		Window::~Window()
		{
			//glfwTerminate();
		}

		void Window::Destroy() const
		{
			glfwDestroyWindow(_window);
			instance = NULL;
		}

		void Window::isInstanceCreated()
		{
			if (!instance)
			{
				throw "Window instance not created! Please use SetWindows method.";
			}
		}

		void Window::Close() const
		{
			glfwSetWindowShouldClose(_window, GLFW_TRUE);
		}

		void Window::SetWindow(const char* title, int width, int height)
		{
			if (!instance)
			{
				instance = new Window(title, width, height);
			}
		}

		void Window::SetWindow(const char* title)
		{
			if (!instance)
			{
				instance = new Window(title);
			}
		}

		void Window::Initialize()
		{
			isInstanceCreated();
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			if (_isFullScreen)
			{
				GLFWmonitor* primalMonitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(primalMonitor);
				_width = mode->width;
				_height = mode->height;
				_window = glfwCreateWindow(_width, _height, _title, primalMonitor, NULL);
			}
			else
			{
				_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
			}
			if (!_window)
			{
				glfwTerminate();
				throw "Failed to create GLFW window";
			}
			glfwMakeContextCurrent(_window);
			//glfwSetWindowUserPointer(_window, instance);
			Input::Input::Initalize();
			glfwSetKeyCallback(_window, Input::Input::key_callback);
			glfwSetMouseButtonCallback(_window, Input::Input::mouse_button_callback);

			// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
			//glewExperimental = GL_TRUE;
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
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				throw error;
			}
			glfwPollEvents();
			glfwSwapBuffers(_window);
		}

		void Window::Clear() const
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}