#include <iostream>
#include <Core/Math.h>
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

		Matrix4x4 myMatrix(new float[4][4]{
			{ 1,2,3,4 },
			{ 5,6,7,8 },
			{ 9,10,11,12 },
			{ 13,14,15,16 },
		});
		std::cout << myMatrix << std::endl;
		std::cout << Matrix4x4::identity << std::endl;

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
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		system("PAUSE");
	}
	return 0;
}