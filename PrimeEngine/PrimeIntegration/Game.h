#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;
using namespace Networking;

using std::cout;
using std::cin;
using std::endl;

class TestGame : public PrimeEngineBase
{
private:
	GameLayer* gameLayer;
	Camera* mainCamera;
	GameObject *player;
	Mesh* cube;

public:
	~TestGame() 
	{
		delete gameLayer;
		delete player;
		delete cube;
	}
	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};