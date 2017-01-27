#include "Graphics/Window.h"
#include "Input.h"

namespace PrimeEngine { namespace Input {

	bool Input::keyPressed[GLFW_KEY_LAST + 1];
	bool Input::mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST + 1];

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		keyPressed[key] = action != GLFW_RELEASE;
	}

	void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		mouseButtonPressed[button] = action != GLFW_RELEASE;
	}

	void Input::Initalize()
	{
		for (int i = 0; i < GLFW_KEY_LAST + 1; i++)
		{
			keyPressed[i] = false;
		}
	}

	bool Input::KeyPressed(const unsigned int& key)
	{
		if (key > GLFW_KEY_LAST)
		{
			throw "Key doesn't exist!";
		}
		return keyPressed[key];
	}

	bool Input::MouseButtonPressed(unsigned int mouseButton)
	{
		if (mouseButton > GLFW_MOUSE_BUTTON_LAST)
		{
			throw "Mouse button doesn't exist!";
		}
		return mouseButtonPressed[mouseButton];
	}
}}