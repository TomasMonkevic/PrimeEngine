#ifndef PRIMEENGINE_INPUT
#define PRIMEENGINE_INPUT

#include "Math\Vector2.h"
#include "DllExport.h"

namespace PrimeEngine { namespace Input {

	//TODO: add key states: down, pressed, released;
	class PRIMEENGINEAPI Input
	{
		friend void Graphics::Window::Initialize();
	private:
		static Math::Vector2 mousePosition;
		static bool keyPressed[GLFW_KEY_LAST + 1];
		static bool mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST + 1];
	private:
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void Initalize();
	public:
		static inline const Math::Vector2& GetMousePosition() { return mousePosition; };
		static bool KeyPressed(const unsigned int& key);
		static bool MouseButtonPressed(unsigned int mouseButton);
	};

}}

#endif //PRIMEENGINE_INPUT