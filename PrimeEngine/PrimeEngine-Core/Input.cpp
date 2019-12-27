#include "Graphics/Window.h"
#include "Input.h"
#include <Utilities/Log.h>

namespace PrimeEngine { namespace Input {

	KeyState InputPC::keyPressed[InputPC::MAX_KEY_COUNT];
	KeyState InputPC::mouseButtonPressed[InputPC::MAX_MOUSE_BUTTON_COUNT];
	Math::Vector2 InputPC::mousePosition = Math::Vector2();
	int32_t InputPC::touchCount;
	bool InputPC::isClear;
	std::vector<Touch> InputPC::touches;

#ifdef PE_ANDROID
#else
	void InputPC::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePosition.x = (float)xpos;
		mousePosition.y = (float)ypos;
	}

	void InputPC::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (action == GLFW_PRESS)
		{
			keyPressed[key] = KeyState::down;
		}
		else if (action == GLFW_RELEASE)
		{
			keyPressed[key] = KeyState::up;
		}
	}

	void InputPC::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			mouseButtonPressed[button] = KeyState::down;
		}
		else if (action == GLFW_RELEASE)
		{
			mouseButtonPressed[button] = KeyState::up;
		}
	}
#endif

	void InputPC::Initalize()
	{
		touchCount = 0;
		isClear = false;
		for (int i = 0; i < MAX_KEY_COUNT; i++)
		{
			keyPressed[i] = KeyState::released;
		}
		for (int i = 0; i < MAX_MOUSE_BUTTON_COUNT; i++)
		{
			mouseButtonPressed[i] = KeyState::released;
		}
	}

	bool InputPC::GetKeyDown(unsigned key)
	{
		if (key > KEY_LAST)
		{
			throw "Key doesn't exist!";
		}
		if (keyPressed[key] == KeyState::down)
		{
			keyPressed[key] = KeyState::pressed;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputPC::GetKey(unsigned key)
	{
		if (key > KEY_LAST)
		{
			throw "Key doesn't exist!";
		}
		return keyPressed[key] == KeyState::pressed || keyPressed[key] == KeyState::down;
	}

	bool InputPC::GetKeyUp(unsigned key)
	{
		if (key > KEY_LAST)
		{
			throw "Key doesn't exist!";
		}
		if (keyPressed[key] == KeyState::up)
		{
			keyPressed[key] = KeyState::released;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputPC::GetMouseButtonDown(unsigned mouseButton)
	{
		if (mouseButton > MOUSE_BUTTON_LAST)
		{
			throw "Button doesn't exist!";
		}
		if (mouseButtonPressed[mouseButton] == KeyState::down)
		{
			mouseButtonPressed[mouseButton] = KeyState::pressed;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputPC::GetMouseButton(unsigned mouseButton)
	{
		if (mouseButton > MOUSE_BUTTON_LAST)
		{
			throw "Button doesn't exist!";
		}
		return mouseButtonPressed[mouseButton] == KeyState::pressed || mouseButtonPressed[mouseButton] == KeyState::down;
	}

	bool InputPC::GetMouseButtonUp(unsigned mouseButton)
	{
		if (mouseButton > MOUSE_BUTTON_LAST)
		{
			throw "Button doesn't exist!";
		}
		if (mouseButtonPressed[mouseButton] == KeyState::up)
		{
			mouseButtonPressed[mouseButton] = KeyState::released;
			return true;
		}
		else
		{
			return false;
		}
	}

	void InputPC::ClearTouches()
	{
        for (auto it = touches.begin(); it != touches.end(); ) {
            if(it->phase == TouchPhase::ENDED) {
                it = touches.erase(it);
                continue;
            }

            it->deltaPosition = Math::Vector2::zero();
            if(it->phase == TouchPhase::BEGAN) {
                //the phase is changed in sync with frames so after firs frame change state to moved
                it->phase = TouchPhase::MOVED;
            }
            ++it;
        }
        //Input::InputPC::touches.erase(it);

        //if(isClear)
		//{

		//    touches.clear();
		//	touchCount = 0;
		//}
	}
}}