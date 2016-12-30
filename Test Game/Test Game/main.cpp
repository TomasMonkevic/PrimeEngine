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
		Window::SetWindow("Test Game", 800, 600);
		Window* gameWindow = Window::GetWindow();
		gameWindow->Initialize();
		while (!gameWindow->Closed())
		{
			if (Input::KeyPressed('W'))
			{
				std::cout << "Pressed!" << std::endl;
			}
			gameWindow->Update();
		}
	}
	catch(char* msg)
	{
		std::cout << msg << std::endl;
		system("PAUSE");
	}
	return 0;
}