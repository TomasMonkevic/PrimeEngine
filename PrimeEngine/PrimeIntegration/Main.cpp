#include "FlappyBird.h"

int main()
{
	try
	{
		FlappyBird* flappyBirdGame = new FlappyBird;
		flappyBirdGame->Play();
	}
	catch (const PrimeEngine::PrimeException& ex) //implement in engine?
	{
		//destroy window
		std::cout << ex.what() << " " << ex.GetErrorCode() << std::endl;
		system("PAUSE");
	}
	return 0;
}