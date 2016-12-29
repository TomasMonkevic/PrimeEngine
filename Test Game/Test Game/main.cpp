#include <iostream>
#include <Vector3.h>
#include <Window.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;

int main()
{
	Window::SetWindow("Test Game", 800, 600);
	Window gameWindow("Test Game", 800, 600);
	gameWindow.Initialize();
	while (!gameWindow.Closed())
	{
		gameWindow.Update();
	}
	return 0;
}