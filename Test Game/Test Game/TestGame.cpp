#include <iostream>

#include <PrimeEngine.h>

#include <Networking\NetworkClient.h>
#include <Networking\NetworkHost.h>

#include <Utilities\Time.h>

#include <Core\Math.h>
#include <Input.h>
#include <PrimeException.h>

#include <Graphics\Window.h>
#include <Graphics\Shader.h>
#include <Graphics\Camera.h>
#include <Graphics\SimpleSprite.h>
#include <Graphics\Sprite.h>
#include <Graphics\SimpleRenderer2D.h>
#include <Graphics\BatchRenderer2D.h>
#include <Graphics\Layers\Layer.h>
#include <Graphics\Layers\Group.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;
using namespace PrimeEngine::Networking;
//using namespace PrimeEngine;

using std::cout;
using std::cin;
using std::endl;

#if _DEBUG //need to add a more advanced loggin system to engine
#define LOG(x) cout<<x<<endl;
#else
#define LOG(x)
#endif // _DEBUG

class FakeUILayer : public Layer
{
public:
	FakeUILayer(Shader* shader) :
		Layer(new BatchRenderer2D(), new Camera(shader, Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)))
	{
		camera->SetPosition(Vector3::zero);
		camera->LookAt(camera->GetPosition() + Vector3::back);
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

class TestGame : public PrimeEngine::PrimeEngine
{
private:
	float speed = 0.1f, scaleSpeed = 0.005f, cameraSpeed = 0.05f;
	Shader *gameShader, *uiShader;
	GameLayer* gameLayer;
	FakeUILayer* uiLayer;
	Sprite *sprite1;
	Group *button, *buttonContainer;
	Camera* mainCamera;

public:

	TestGame()
	{

	}

	~TestGame()
	{
		//delete all stuff
	}

	void Awake() override
	{
		//CreateWin("Tik Tac Toe", 1366, 768);
		CreateWin("Test Game", 800, 600);
		GetWindow()->EnableVSync(true);
		GetWindow()->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));

		Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
		//Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

		gameShader = new Shader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");

		uiShader = new Shader("..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.vert",
			"..\\..\\PrimeEngine\\PrimeEngine\\Shaders\\standard.frag");

		mainCamera = new Camera(gameShader, pr);

		//Vector3 cameraPosition(Vector3(9, 4.5f, -6.0f)); //projection
		Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
		mainCamera->SetPosition(cameraPosition);

		Sprite* backGround = new Sprite(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1));
		sprite1 = new Sprite(Vector3(5, 4.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1));

		gameLayer = new GameLayer(mainCamera);
		gameLayer->Submit(backGround);
		gameLayer->Submit(sprite1);

		buttonContainer = new Group(Vector3(-6, 0, 0), Vector2(10, 10));
		button = new Group(Vector3(0, 1.5f, 0), Vector2(10, 10));
		Sprite* uiEl = new Sprite(Vector3(0, 0, 0), Vector2(4, 1), Vector4(1.0f, 0.0f, 0.0f, 1));
		buttonContainer->Add(button);
		buttonContainer->Add(uiEl);
		button->Add(new Sprite(Vector3(0, 0.0f, 0), Vector2(4, 1), Vector4(1.0f, 0.0f, 0.0f, 1)));
		button->Add(new Sprite(Vector3(0, 0.0f, 0), Vector2(3, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1)));
		uiLayer = new FakeUILayer(uiShader);
		uiLayer->Submit(buttonContainer);
	}

	void Update() override
	{
		//Change light position
		Vector3 opa = mainCamera->ScreenToWorldPoint(Input::GetMousePosition());
		Vector3 opa2 = uiLayer->camera->ScreenToWorldPoint(Input::GetMousePosition());
		gameShader->SetUniform("lightPosition", Vector2(opa.x, opa.y));
		uiShader->SetUniform("lightPosition", Vector2(opa2.x, opa2.y));

		//Rotate ui
		buttonContainer->Rotate(0.1f, Vector3::forward);
		button->Rotate(0.1f, Vector3::forward);

		sprite1->Rotate(0.1f, Vector3::forward);
		if (Input::KeyPressed(256)) //esc
		{
			GetWindow()->Close();
		}
	}

	void Tick() override
	{
		LOG(GetFPS() << "fps");
	}

	void Render() override
	{
		gameLayer->Render();
		uiLayer->Render();
		mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
		mainCamera->Render();
	}
};

int main()
{
	try
	{
		TestGame testGame;
		testGame.Play();
	}
	catch (const PrimeEngine::PrimeException& ex) //implement in engine?
	{
		//destroy window
		std::cout << ex.what() << " " << ex.GetErrorCode() << std::endl;
		system("PAUSE");
	}
	return 0;
}