#include "FlappyBird.h"
#include "Game.h"

int main()
{
	try
	{
		//PrimeEngineBase* game = new FlappyBird;
		PrimeEngineBase* game = new TestGame;
		game->Play();
	}
	catch (const PrimeEngine::PrimeException& ex) //implement in engine?
	{
		//destroy window
		std::cout << ex.what() << " " << ex.GetErrorCode() << std::endl;
		system("PAUSE");
	}
	return 0;
}