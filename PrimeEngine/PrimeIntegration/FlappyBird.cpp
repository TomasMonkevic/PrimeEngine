#define P_LOG_LEVEL 2

#include "FlappyBird.h"

FlappyBrid::~FlappyBrid()
{
	delete playingLayer;
	delete mainCamera;
	delete bird;
	delete background;
	delete ground;
}

void FlappyBrid::Gravity(GameObject& obj)
{
	float groundY = ground->GetTransform().GetPosition().y + 28.0f;
	float gravity = 9.8f, mass = 50.0f;
	obj.GetTransform().SetPosition(obj.GetTransform().GetPosition() + Vector3::down() * GetDeltaTime() * gravity * mass);
	obj.GetTransform().SetPosition(Vector2(obj.GetTransform().GetPosition().x, max(groundY, obj.GetTransform().GetPosition().y)));
}

void FlappyBrid::Awake()
{
	//Windows setup
	CreateWin("Flappy Bird", 720, 1280);
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Color(84, 192, 201));

	//Setup layer
	//TODO make a main camera in gameLayer or return a handle to camera; think about the camera system
	mainCamera = new Camera(ShaderManagerI->CreateShader("mainShader", Shader::default), Matrix4x4::Orthographic(-360.0f, 360.0f, -640.0f, 640.0f, -1.0f, 1.0f));
	playingLayer = new GameLayer(mainCamera);

	float scale = 5.0f; //5.0f

	bird = new GameObject();
	bird->AddComponent(new Sprite(Vector2(17.0f, 12.0f) * scale, "Resources\\Textures\\bird1.png")); //TODO think about scale and sprite size

	background = new GameObject(Vector2(0.0f, -125.0f));
	background->AddComponent(new Sprite(Vector2(144.0f, 256.0f) * scale, "Resources\\Textures\\dayBg.png"));

	ground = new GameObject(Vector2(0.0f, -612.0f));
	ground->AddComponent(new Sprite(Vector2(168.0f, 56.0f) * scale, "Resources\\Textures\\ground.png"));

	playingLayer->Submit(background);
	playingLayer->Submit(ground);
	playingLayer->Submit(bird);
}

void FlappyBrid::Update()
{
	if (InputPC::KeyPressed(32))
	{
		PRIME_INFO("Jump");
		bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::up() * 100.0f);
	}
	bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::right() * GetDeltaTime() * 50.0f);
	Gravity(*bird);
}

void FlappyBrid::Tick()
{

}

void FlappyBrid::Render()
{
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back()); //TODO move this to engine
	mainCamera->SetPosition(Vector2(bird->GetTransform().GetPosition().x, mainCamera->GetPosition().y));
	playingLayer->Render();
}