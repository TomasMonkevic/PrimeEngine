#ifndef PRIMEENGINE_INPUT
#define PRIMEENGINE_INPUT

#include <GLFW/glfw3.h> //probably not needed
#include "DllExport.h"

namespace PrimeEngine { namespace Input {

	//TODO: add key states: down, pressed, released;
	class PRIMEENGINEAPI Input
	{
		friend void Graphics::Window::Initialize();
	private:
		static bool keyPressed[GLFW_KEY_LAST + 1];
		static bool mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST + 1];
	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void Initalize();
	public:
		//TODO: mouse position with vector 2d
		static bool KeyPressed(unsigned int key);
		static bool MouseButtonPressed(unsigned int mouseButton);
	};

}}

#endif //PRIMEENGINE_INPUT