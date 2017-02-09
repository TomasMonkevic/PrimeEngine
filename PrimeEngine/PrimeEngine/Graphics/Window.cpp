#include "Window.h"
#include "..\Input.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		Window* Window::instance = NULL;

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			//would be nice to change window fields
			//save the aspect ratio
			glViewport(0, 0, width, height);
		}

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
			glfwTerminate();
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
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //for now
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
			glfwSetWindowAspectRatio(_window, _width, _height);
			Input::Input::Initalize(); //move to a seperate function
			glfwSetKeyCallback(_window, Input::Input::key_callback);
			glfwSetMouseButtonCallback(_window, Input::Input::mouse_button_callback);
			glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
			glfwSwapInterval(1); //Vsync off-0, on-1
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
#ifdef DEBUG
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				throw error;
			}
#endif // DEBUG
			glfwPollEvents();
			glfwSwapBuffers(_window);
		}

		void Window::Clear() const
		{
			glClearColor(_color.x, _color.y, _color.z, _color.w);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}