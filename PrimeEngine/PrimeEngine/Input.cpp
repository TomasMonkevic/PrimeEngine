#include "Graphics/Window.h"
#include "Input.h"

namespace PrimeEngine { namespace Input {

	bool Input::keyPressed[GLFW_KEY_LAST + 1];
	bool Input::mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST + 1];
	Math::Vector2 Input::mousePosition = Math::Vector2();

	void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePosition.x = xpos;
		mousePosition.y = ypos;//::Window::GetWindow()->GetSize().y - ypos; //change it back?
	}

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
		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++)
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