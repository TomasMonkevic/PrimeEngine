#pragma once

#include "Math\Vector2.h"
#include "DllExport.h"

namespace PrimeEngine { namespace Input {

	enum class KeyState
	{
		released = 0,
		down,
		pressed,
		up
	};

	class PRIMEENGINEAPI InputPC
	{
		friend void Graphics::Window::Initialize();
	private:
		static Math::Vector2 mousePosition;
		static KeyState keyPressed[GLFW_KEY_LAST + 1];
		static KeyState mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST + 1];
	private:
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void Initalize();
	public:
		static inline const Math::Vector2& GetMousePosition() { return mousePosition; };

		static bool GetKeyDown(unsigned key);
		static bool GetKey(unsigned key);
		static bool GetKeyUp(unsigned key);

		static bool GetMouseButtonDown(unsigned mouseButton);
		static bool GetMouseButton(unsigned mouseButton);
		static bool GetMouseButtonUp(unsigned mouseButton);
	};

}}