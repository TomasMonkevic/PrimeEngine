#include <iostream>

#include <PrimeEngine.h>

#include <Networking\TCPServer.h>
#include <Networking\TCPClient.h>

#include <Utilities\Time.h>
#include <Utilities\Log.h>

#include <Math/Math.h>
#include <Input.h>
#include <PrimeException.h>

#include <Graphics\Window.h>
#include <Graphics\Shader\Shader.h>
#include <Graphics\Camera.h>
#include <Graphics\Sprite.h>
#include <Graphics\BatchRenderer2D.h>
#include <Graphics\Layers\UILayer.h>
#include <Graphics\Layers\GameLayer.h>
#include <Graphics\Texture.h>
#include <UI\Text.h>

#include <GameObject.h>

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