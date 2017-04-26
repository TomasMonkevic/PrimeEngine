#include "Window.h"
#include "..\Input.h"
#include "..\PrimeException.h"
#include "..\Utilities\Log.h"

namespace PrimeEngine
{
	namespace Graphics
	{
		Window* Window::instance = NULL;

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			Window::GetWindow()->_width = width;
			Window::GetWindow()->_height = height;
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
				PrimeException windowNotInit("Window instance not created! Please use SetWindows method.", (int)glGetError());
				throw windowNotInit;
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
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //for now always is resizable
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
				PrimeException windowNotInit("Failed to create GLFW window", (int)glGetError());
				throw windowNotInit;
			}
			glfwMakeContextCurrent(_window);
			glfwSetWindowAspectRatio(_window, _width, _height);

			Input::Input::Initalize(); //move to a seperate function
			glfwSetKeyCallback(_window, Input::Input::key_callback);
			glfwSetMouseButtonCallback(_window, Input::Input::mouse_button_callback);
			glfwSetCursorPosCallback(_window, Input::Input::cursor_position_callback);

			glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
			//glfwSwapInterval(1); //Vsync off-0, on-1
			//EnableVSync();
			// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				PrimeException windowNotInit("Failed to initialize GLEW", (int)glGetError());
				throw windowNotInit;
			}
			glViewport(0, 0, _width, _height);
			PRIME_INFO(glGetString(GL_VERSION), "\n");
			PRIME_INFO(glGetString(GL_VENDOR), "\n");
			PRIME_INFO(glGetString(GL_RENDERER), "\n");
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(_window) == 1;
		}

		void Window::Update() const
		{
#ifdef _DEBUG
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				PrimeException windowNotInit("GLEW error occured", (int)error);
				throw windowNotInit;
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