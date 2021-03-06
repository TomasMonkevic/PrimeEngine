#include <Platforms/Desktop/DesktopWindow.h>

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
			GetWindow()->SetSize(width, height);
			GlCall(glViewport(0, 0, width, height));
		}

		DesktopWindow::~DesktopWindow()
		{
			glfwTerminate();
		}

		void DesktopWindow::SetFullscreen(bool isFullscreen) {
			_isFullScreen = isFullscreen;
		}

		void DesktopWindow::EnableVSync(bool isEnabled)
		{
			glfwSwapInterval((GLint)isEnabled);
		}

		void DesktopWindow::Close()
		{
			glfwSetWindowShouldClose(_window, GLFW_TRUE);
		}

		void DesktopWindow::Initialize()
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

			// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
			GlCall(glewExperimental = GL_TRUE);
			GlCall(GLenum glStatus = glewInit());
			if (glStatus != GLEW_OK)
			{
				PrimeException windowNotInit("Failed to initialize GLEW", (int)glGetError());
				throw windowNotInit;
			}
			GlCall(glViewport(0, 0, _width, _height));

			GlCall(glEnable(GL_BLEND));
			GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			//glEnable(GL_MULTISAMPLE);

			PRIME_INFO(glGetString(GL_VERSION), "\n");
			PRIME_INFO(glGetString(GL_VENDOR), "\n");
			PRIME_INFO(glGetString(GL_RENDERER), "\n");
		}

		void DesktopWindow::Update()
		{
            glfwPollEvents();
			glfwSwapBuffers(_window);
		}

		bool DesktopWindow::IsReady() const {
			return true;
		}

		void DesktopWindow::Destroy()
		{
			glfwDestroyWindow(_window);
		}

		bool DesktopWindow::IsClosed() const
		{
			return glfwWindowShouldClose(_window) == 1;
		}

		void DesktopWindow::SetTitle(const char* title)
		{
			_title = title;
		}

		const char* DesktopWindow::GetTitle() const
		{
			return _title;
		}
	}
}