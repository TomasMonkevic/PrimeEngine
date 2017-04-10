#include "TestGame.h"
#include <TestTexture.h>

#define TEST_GAME false

int main()
{
#if TEST_GAME
	try
	{
		TestGame testGame;
		testGame.Play();
	}
	catch (const PrimeEngine::PrimeException& ex) //implement in engine?
	{
		//destroy window
		cout << ex.what() << " " << ex.GetErrorCode() << endl;
		system("PAUSE");
	}
#endif
	cout << "Opa" << endl;
	PrimeEngine::TestTexture("texture.png");
	return 0;
}