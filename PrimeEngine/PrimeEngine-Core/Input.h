#pragma once

#include "Math/Vector2.h"
#include "DllExport.h"
#include "stdint.h"
#include <vector>
#include "Graphics/Window.h"

namespace PrimeEngine { namespace Input {

    enum class TouchPhase {
        BEGAN = 0,
        MOVED = 1,
        ENDED = 2
    };

    struct Touch {
        TouchPhase phase;
        PrimeEngine::Math::Vector2 position;
        PrimeEngine::Math::Vector2 deltaPosition;
        int32_t fingerId;

        Touch() : Touch(0) {}
		Touch(int32_t fId) : fingerId(fId) {}

        bool operator==(const Touch& obj) {
            return fingerId == obj.fingerId;
        }

        bool operator!=(const Touch& obj) {
            return !(*this == obj);
        }
    };

	enum class KeyState
	{
		released = 0,
		down,
		pressed,
		up
	};

	class PRIMEENGINEAPI InputPC
	{
#ifdef PE_ANDROID
#else
		friend void Graphics::Window::Initialize();
#endif
	public:
#ifdef PE_ANDROID
		static const int32_t KEY_LAST = 255;
		static const int32_t MOUSE_BUTTON_LAST = 0;
#else
		static const int32_t KEY_LAST = GLFW_KEY_LAST;
		static const int32_t MOUSE_BUTTON_LAST = GLFW_KEY_LAST;
#endif
		static const int32_t MAX_KEY_COUNT = KEY_LAST + 1;
		static const int32_t MAX_MOUSE_BUTTON_COUNT = MOUSE_BUTTON_LAST + 1;
	private:
		static Math::Vector2 mousePosition;
		static KeyState keyPressed[MAX_KEY_COUNT];
		static KeyState mouseButtonPressed[MAX_MOUSE_BUTTON_COUNT];
	private:
#ifdef PE_ANDROID
#else
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
#endif
	public:
        static std::vector<Touch> touches;

        static void Initalize();

        static inline const Math::Vector2& GetMousePosition() { return mousePosition; };

		static bool GetKeyDown(unsigned key);
		static bool GetKey(unsigned key);
		static bool GetKeyUp(unsigned key);

		static bool GetMouseButtonDown(unsigned mouseButton);
		static bool GetMouseButton(unsigned mouseButton);
		static bool GetMouseButtonUp(unsigned mouseButton);

		static void ProcessTouches();
		static std::vector<Touch> GetTouches() { return touches; }

	};

}}