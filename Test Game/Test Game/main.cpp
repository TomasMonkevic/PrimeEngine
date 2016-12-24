#include <iomanip> //temp
#include <Vector3.h>
#include <iostream>

using namespace PrimeEngine::Math;
using namespace std;

int main()
{
	Vector3* omg = new Vector3(1, 1, 2);
	Vector3* omg2 = new Vector3(2, 1, 2);
	Vector3* rez = omg;
	rez->x = 0.0f;
	cout << omg->x << " " << omg->y << " " << omg->z << endl;
	cout << rez->x << " " << rez->y << " " << rez->z << endl;
	system("PAUSE"); //temp
}