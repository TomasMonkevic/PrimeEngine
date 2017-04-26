#include "Graphics/Window.h"
#include "Input.h"

namespace PrimeEngine { namespace Input {

	bool InputPC::keyPressed[GLFW_KEY_LAST + 1];
	bool InputPC::mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST + 1];
	Math::Vector2 InputPC::mousePosition = Math::Vector2();

	void InputPC::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePosition.x = (float)xpos;
		mousePosition.y = (float)ypos;
	}

	void InputPC::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		keyPressed[key] = action != GLFW_RELEASE;
	}

	void InputPC::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		mouseButtonPressed[button] = action != GLFW_RELEASE;
	}

	void InputPC::Initalize()
	{
		for (int i = 0; i < GLFW_KEY_LAST + 1; i++)
		{
			keyPressed[i] = false;
		}
		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++)
		{
			keyPressed[i] = false;
		}
	}

	bool InputPC::KeyPressed(const unsigned int& key)
	{
		if (key > GLFW_KEY_LAST)
		{
			throw "Key doesn't exist!";
		}
		return keyPressed[key];
	}

	bool InputPC::MouseButtonPressed(unsigned int mouseButton)
	{
		if (mouseButton > GLFW_MOUSE_BUTTON_LAST)
		{
			throw "Mouse button doesn't exist!";
		}
		return mouseButtonPressed[mouseButton];
	}
}}