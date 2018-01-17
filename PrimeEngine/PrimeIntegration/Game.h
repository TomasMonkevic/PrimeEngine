#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;
using namespace Networking;
using namespace PrimeEngine::Graphics::Lights;

using std::cout;
using std::cin;
using std::endl;

class TestGame : public PrimeEngineBase
{
private:
	Scene* mainScene;
	Camera* mainCamera;
	GameObject* player;

public:
	~TestGame() 
	{
		delete mainScene;
	}
	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};