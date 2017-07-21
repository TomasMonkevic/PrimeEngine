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
#include <Graphics\Layers\Layer.h>
#include <Graphics\Texture.h>

#include <GameObject.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;
using namespace Networking;

using std::cout;
using std::cin;
using std::endl;

class FakeUILayer : public Layer
{
public:
	FakeUILayer(Shader* shader) :
		Layer(new BatchRenderer2D(), new Camera(shader, Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)))
	{
		camera->SetPosition(Vector3::zero());
		camera->LookAt(camera->GetPosition() + Vector3::back());
	}
};

class GameLayer : public Layer
{
public:
	GameLayer(Camera* camera) :
		Layer(new BatchRenderer2D(), camera)
	{

	}
};

class TestGame : public PrimeEngineBase
{
private:
	float speed = 10.0f;
	GameLayer* gameLayer;
	FakeUILayer* uiLayer;
	Sprite *sprite1;
	Camera* mainCamera;
	Texture* texture;
	Texture* texture2;
	Texture* texture3;
	Font* myFont;
	GameObject *player, *fpsLabel, *button, *buttonContainer;
	//Label* myLabel;

public:
	~TestGame() 
	{
		delete uiLayer;
		//delete gameLayer;
		delete sprite1;
		delete player;
		//delete button;
		//delete buttonContainer;
	}
	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};