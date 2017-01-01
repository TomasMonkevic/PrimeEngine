#include <iostream>
#include <Vector3.h>
#include <Window.h>
#include <Input.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;

int main()
{
	try
	{
		//Window::SetWindow("Test Game", 1366, 768);
		Window::SetWindow("Test Game", 800, 600);
		//Window::SetWindow("Test Game Full");
		Window* gameWindow = Window::GetWindow();
		gameWindow->Initialize();
		while (!gameWindow->Closed())
		{
			if (Input::KeyPressed('W'))
			{
				gameWindow->Close();
				std::cout << "Pressed!" << std::endl;
			}
			else if (Input::MouseButtonPressed(0))
			{
				std::cout << "Mouse pressed!" << std::endl;
			}
			gameWindow->Update();
		}
		gameWindow->Destroy();
	}
	catch (char* msg)
	{
		std::cout << msg << std::endl;
		system("PAUSE");
	}
	return 0;
}