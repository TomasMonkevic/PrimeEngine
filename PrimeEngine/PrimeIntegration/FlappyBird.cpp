#define P_LOG_LEVEL 2

#include "FlappyBird.h"

#include <thread>

FlappyBird::~FlappyBird()
{
	delete playingLayer;
	delete mainCamera;
	delete bird;
	delete background;
	delete groundPrefab;
}

void FlappyBird::Gravity(GameObject& obj)
{
	Sprite* sprite = groundPrefab->GetComponent<Sprite>();
	float groundY = groundPrefab->GetTransform().GetPosition().y + sprite->GetSize().y / 2.0f + 30.0f; //TODO remove hard coded stuff should be texture size
	float gravity = 9.8f, mass = 55.0f;
	obj.GetTransform().SetPosition(obj.GetTransform().GetPosition() + Vector3::down() * GetDeltaTime() * gravity * mass); //TODO change gravity to accelerate
	obj.GetTransform().SetPosition(Vector2(obj.GetTransform().GetPosition().x, max(groundY, obj.GetTransform().GetPosition().y)));
	//float rotationZ = 0.0f;
	if (obj.GetTransform().GetRotation().EulerAngles().z * (180.0f/PI) > -90.0f)
	{
		//PRIME_INFO(obj.GetTransform().GetRotation().EulerAngles().z * (180.0f / PI), " ", birdRotation, "\n");
		obj.GetTransform().Rotate(Quaternion(0.0f, 0.0f, birdRotation));
		birdRotation -= 150.0f * GetDeltaTime();
	}
}

void FlappyBird::Jump(float height)
{
	//PRIME_INFO("On start: ", bird.GetTransform().GetPosition(), "\n");
	float finish = bird->GetTransform().GetPosition().y + height;
	while (bird->GetTransform().GetPosition().y < finish)
	{
		bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::up() * 25.0f);

		if (bird->GetTransform().GetRotation().EulerAngles().z * (180.0f / PI) < 30.0f)
		{
			//PRIME_INFO("Jump: ", bird->GetTransform().GetRotation().EulerAngles().z * (180.0f / PI), " ", birdRotation, "\n");
			bird->GetTransform().Rotate(Quaternion(0.0f, 0.0f, birdRotation));
			birdRotation += 20.0f;
		}
		Sleep(GetDeltaTime() * 1000);
		//PRIME_INFO(GetDeltaTime(), "\n");
	}
}

void FlappyBird::SpawnGround()
{
	//TODO dont forget to remove ground from layer and delete it
	static float groundPositionX = 0.0f;
	Sprite* sprite = groundPrefab->GetComponent<Sprite>();
	for (int i = 0; i < 10; i++) //temp
	{
		grounds.push_back(new GameObject(*groundPrefab)); //TODO make a copy constructor;
		grounds.back()->GetTransform().SetPosition(Vector2(groundPositionX,grounds.back()->GetTransform().GetPosition().y)); //TODO manipulating objects is a pain, think of something beter
		PRIME_INFO(groundPositionX, grounds.back()->GetTransform().GetPosition(), "\n");
		playingLayer->Submit(grounds.back());
		groundPositionX += sprite->GetSize().x;
	}
}

void FlappyBird::Awake()
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

	groundPrefab = new GameObject(Vector2(0.0f, -612.0f));
	groundPrefab->AddComponent(new Sprite(Vector2(168.0f, 56.0f) * scale, "Resources\\Textures\\ground.png"));

	playingLayer->Submit(background);
	playingLayer->Submit(bird);

	//bird->GetTransform().Rotate(Quaternion(0.0f, 0.0f, -91.0f)); //TEMP!!!!
	//PRIME_INFO(bird->GetTransform().GetRotation().EulerAngles().z * (180.0f / PI), "\n"); //TEMP!!
	SpawnGround(); //temp
}

void FlappyBird::Update()
{
	//PRIME_INFO(GetFPS(), "fps \n");
	if (InputPC::GetKeyDown(32))
	{
		//TODO should be some kind of animation
		//bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::up() * 200.0f);
		std::thread jumpAnim(&FlappyBird::Jump, this, 175.0f);
		jumpAnim.detach();
	}

	bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::right() * GetDeltaTime() * 150.0f);
	background->GetTransform().SetPosition(Vector2(bird->GetTransform().GetPosition().x, background->GetTransform().GetPosition().y));
	Gravity(*bird);
}

void FlappyBird::Tick()
{
	PRIME_INFO(GetFPS(), "fps \n");
	//PRIME_INFO("Brid position: ", bird->GetTransform().GetPosition(), "\n");
}

void FlappyBird::Render()
{
	mainCamera->SetPosition(Vector2(bird->GetTransform().GetPosition().x, mainCamera->GetPosition().y));
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back()); //TODO move this to engine
	playingLayer->Render();
}