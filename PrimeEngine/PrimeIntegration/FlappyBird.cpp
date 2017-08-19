#define P_LOG_LEVEL 2

#include "FlappyBird.h"

#include <thread>

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
	Sprite* sprite = static_cast<Sprite*>(ground->GetComponent<Renderable>());
	float groundY = ground->GetTransform().GetPosition().y + sprite->GetSize().y / 2.0f + 30.0f; //TODO remove hard coded stuff should be texture size
	float gravity = 9.8f, mass = 25.0f;
	obj.GetTransform().SetPosition(obj.GetTransform().GetPosition() + Vector3::down() * GetDeltaTime() * gravity * mass);
	obj.GetTransform().SetPosition(Vector2(obj.GetTransform().GetPosition().x, max(groundY, obj.GetTransform().GetPosition().y)));

	obj.GetTransform().Rotate(90.0f * GetDeltaTime() * 0.01f, Vector3::back());
}

void FlappyBrid::Jump(float height)
{
	//PRIME_INFO("On start: ", bird.GetTransform().GetPosition(), "\n");
	float finish = bird->GetTransform().GetPosition().y + height;
	while (bird->GetTransform().GetPosition().y < finish)
	{
		bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::up() * 20.0f);
		bird->GetTransform().Rotate(90.0f * 0.001f, Vector3::forward());
		Sleep(GetDeltaTime() * 1000);
		//PRIME_INFO(GetDeltaTime(), "\n");
	}
}

void FlappyBrid::Awake()
{
	//Windows setup
	CreateWin("Flappy Bird", 720, 1280);
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Color(84, 192, 201));

	//Setup layer
	PRIME_INFO(sin(90.0f * (PI/180.0f)), '\n');
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
	//PRIME_INFO(GetFPS(), "fps \n");
	if (InputPC::GetKeyDown(32))
	{
		//TODO should be some kind of animation
		//bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::up() * 200.0f);
		std::thread jumpAnim(&FlappyBrid::Jump, this, 150.0f);
		jumpAnim.detach();
	}

	bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::right() * GetDeltaTime() * 70.0f);
	background->GetTransform().SetPosition(Vector2(bird->GetTransform().GetPosition().x, background->GetTransform().GetPosition().y));
	Gravity(*bird);
}

void FlappyBrid::Tick()
{
	PRIME_INFO(GetFPS(), "fps \n");
}

void FlappyBrid::Render()
{
	mainCamera->SetPosition(Vector2(bird->GetTransform().GetPosition().x, mainCamera->GetPosition().y));
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back()); //TODO move this to engine
	playingLayer->Render();
}