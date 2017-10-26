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
	float speed = 10.0f;
	GameLayer* gameLayer;
	UILayer* uiLayer;
	Sprite *sprite1;
	Camera* mainCamera;
	Font* myFont;
	GameObject *player, *fpsLabel, *button, *buttonContainer;
	UI::Text* testText;

public:
	~TestGame() 
	{
		delete testText;
		delete gameLayer;
		delete sprite1;
		delete player;
		delete button;
		delete fpsLabel;
		delete buttonContainer;
	}
	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};