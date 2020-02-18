#include <Graphics/Window.h

#include <Input.h>
#include <PrimeException.h>
#include <Utilities/Log.h>
#include <memory>

namespace PrimeEngine
{
	namespace Graphics
	{
        BasicWindow* GetWindow() {
            static std::unique_ptr<BasicWindow> window = std::make_unique<DesktopWindow>();
            return window.get();
        }

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
            //TODO this should be moved to SetViewportSize?
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
			#ifndef PE_ANDROID
			glfwTerminate();
			#endif
		}

		void Window::Destroy()
		{
			#ifdef PE_ANDROID
            if (_display != EGL_NO_DISPLAY) {
                eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                if (_context != EGL_NO_CONTEXT) {
                    eglDestroyContext(_display, _context);
                }
                if (_surface != EGL_NO_SURFACE) {
                    eglDestroySurface(_display, _surface);
                }
                eglTerminate(_display);
            }
            _display = EGL_NO_DISPLAY;
            _context = EGL_NO_CONTEXT;
            _surface = EGL_NO_SURFACE;
            #else
			glfwDestroyWindow(_window);
			#endif
			delete instance;
			instance = nullptr;
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
			#ifndef PE_ANDROID
			glfwSetWindowShouldClose(_window, GLFW_TRUE);
			#endif
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
			glfwInit();
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //for now always is resizable
			//glfwWindowHint(GLFW_SAMPLES, 4); //aa
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

			Input::InputPC::Initalize(); //move to a seperate function
			glfwSetKeyCallback(_window, Input::InputPC::key_callback);
			glfwSetMouseButtonCallback(_window, Input::InputPC::mouse_button_callback);
			glfwSetCursorPosCallback(_window, Input::InputPC::cursor_position_callback);

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
			#endif
			glViewport(0, 0, _width, _height);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//glEnable(GL_MULTISAMPLE);

			PRIME_INFO(glGetString(GL_VERSION), "\n");
			PRIME_INFO(glGetString(GL_VENDOR), "\n");
			PRIME_INFO(glGetString(GL_RENDERER), "\n");
		}

		bool Window::Closed() const
		{
			#ifndef PE_ANDROID
			return glfwWindowShouldClose(_window) == 1;
			#else
			return false;
			#endif
		}

		void Window::Update() const
		{
#ifdef _DEBUG
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				PrimeException windowNotInit("GLEW error occured", (int)error);
				PRIME_INFO(glewGetErrorString(error),'\n');
				throw windowNotInit;
			}
#endif // DEBUG
			#ifdef PE_ANDROID
            eglSwapBuffers(_display, _surface);
            #else
            glfwPollEvents();
			glfwSwapBuffers(_window);
			#endif
			
		}

		void Window::Clear() const
		{
			glClearColor(_color[0], _color[1], _color[2], _color[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}