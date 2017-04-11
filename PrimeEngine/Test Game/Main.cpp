#include "TestGame.h"

#define TEST_GAME true

int main()
{
#if TEST_GAME
	try
	{
		TestGame* testGame = new TestGame();
		testGame->Play();
	}
	catch (const PrimeEngine::PrimeException& ex) //implement in engine?
	{
		//destroy window
		cout << ex.what() << " " << ex.GetErrorCode() << endl;
		system("PAUSE");
	}
#endif
	cout << "Opa" << endl;
	return 0;
}