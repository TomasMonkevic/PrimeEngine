#define P_LOG_LEVEL 2

#include "FlappyBird.h"

#include <thread>

#define PIPE_GAP 300.0f

FlappyBird::~FlappyBird()
{
	delete playingLayer;
	delete mainCamera;
	delete bird;
	delete background;
	delete groundPrefab;
	delete pipeBottomPrefab;
	delete pipeTopPrefab;
}

void FlappyBird::Gravity(GameObject& obj)
{
	Sprite* sprite = groundPrefab->GetComponent<Sprite>();
	float groundY = groundPrefab->GetTransform().Position.y + sprite->GetSize().y / 2.0f + 30.0f; //TODO remove hard coded stuff should be texture size
	float gravity = 9.8f, mass = 55.0f;
	obj.GetTransform().Position = obj.GetTransform().Position + Vector3::down() * GetDeltaTime() * gravity * mass; //TODO change gravity to accelerate
	obj.GetTransform().Position.y = max(groundY, obj.GetTransform().Position.y);
	//float rotationZ = 0.0f;
	if (obj.GetTransform().Rotation.EulerAngles().z * (180.0f/PI) > -90.0f)
	{
		//PRIME_INFO(obj.GetTransform().GetRotation().EulerAngles().z * (180.0f / PI), " ", birdRotation, "\n");
		//TODO change the rotation to not needing birdRotation. use multiplication
		obj.GetTransform().Rotate(Quaternion(0.0f, 0.0f, birdRotation));
		birdRotation -= 150.0f * GetDeltaTime();
	}
}

void FlappyBird::Jump(float height) //TODO try out animation idey (hardcode this function to update)
{
	//PRIME_INFO("On start: ", bird.GetTransform().GetPosition(), "\n");
	float finish = bird->GetTransform().Position.y + height;
	while (bird->GetTransform().Position.y < finish)
	{
		bird->GetTransform().Position = bird->GetTransform().Position + Vector3::up() * 25.0f;

		if (bird->GetTransform().Rotation.EulerAngles().z * (180.0f / PI) < 30.0f)
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

	float width = groundPrefab->GetComponent<Sprite>()->GetSize().x;

	//PRIME_INFO(mainCamera->WorldToViewPoint(grounds.back()->GetTransform().GetPosition() + Vector2(width / 2.0f, 0.0f)).x, "\n");
	if (mainCamera->WorldToViewPoint(grounds.back()->GetTransform().Position - Vector2(width / 2.0f, 0.0f)).x <= -1.0f)
	{
		//PRIME_INFO(mainCamera->WorldToViewPoint(Vector2(nextPoint, 0.0f)), "\n");
		PRIME_INFO("Ground spawned! \n");
		groundPositionX += width;
		grounds.push_back(new GameObject(*groundPrefab));
		//TODO manipulating objects is a pain, think of something beter
		grounds.back()->GetTransform().Position.x = groundPositionX;
		playingLayer->Submit(grounds.back());
	}
	if (mainCamera->WorldToViewPoint(grounds[0]->GetTransform().Position + Vector2(width / 2.0f, 0.0f)).x <= -2.0f)
	{
		PRIME_INFO("Ground deleted \n");
		playingLayer->Remove(grounds[0]);
		delete grounds[0];
		grounds.erase(grounds.begin());
		//TODO deep copy all pointers in component system
	}
}

void FlappyBird::SpawnPipes()
{
	float initialPos = mainCamera->ViewportToWorldPoint(Vector2(1.0f, 0.0f)).x;
	static float nextPipePosition = initialPos;
	float width = pipeBottomPrefab->GetComponent<Sprite>()->GetSize().x; 

	if (nextPipePosition == initialPos)
	{
		//pipes.push_back(new GameObject(*pipeBottomPrefab));
		//pipes.back()->GetTransform().Position.x = nextPipePosition;
		pipes.push_back(new GameObject(*pipeTopPrefab));
		pipes.back()->GetTransform().Position.x = nextPipePosition;
	}

	if (mainCamera->WorldToViewPoint(pipes.back()->GetTransform().Position - Vector2(width / 2.0f, 0.0f)).x <= 1.0f)
	{
		PRIME_INFO("Pipe spawned! \n");
		playingLayer->Submit(pipes.back());
		nextPipePosition += PIPE_GAP;

		if (nextPipePosition != initialPos)
		{
			//pipes.push_back(new GameObject(*pipeBottomPrefab));
			//pipes.back()->GetTransform().Position.x = nextPipePosition;
			pipes.push_back(new GameObject(*pipeTopPrefab));
			pipes.back()->GetTransform().Position.x = nextPipePosition;
		}
	}

	if (mainCamera->WorldToViewPoint(pipes[0]->GetTransform().Position + Vector2(width / 2.0f, 0.0f)).x <= -2.0f)
	{
		PRIME_INFO("Pipes deleted \n");
		playingLayer->Remove(pipes[0]);
		delete pipes[0];
		pipes.erase(pipes.begin());
		//TODO deep copy all pointers in component system
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

	background = new GameObject(Vector2(0.0f, -125.0f)); //TODO remove hardcoded values
	background->AddComponent(new Sprite(Vector2(144.0f, 256.0f) * scale, "Resources\\Textures\\dayBg.png"));

	groundPrefab = new GameObject(Vector2(0.0f, -612.0f));
	groundPrefab->AddComponent(new Sprite(Vector2(168.0f, 56.0f) * scale, "Resources\\Textures\\ground.png"));

	pipeBottomPrefab = new GameObject(Vector2(0.0f, 100.0f));
	pipeBottomPrefab->AddComponent(new Sprite(Vector2(26.0f, 160.0f) * scale, "Resources\\Textures\\pipeBottom.png"));

	pipeTopPrefab = new GameObject(Vector2(0.0f, -100.0f));
	pipeTopPrefab->AddComponent(new Sprite(Vector2(26.0f, 160.0f) * scale, "Resources\\Textures\\pipeTop.png"));

	grounds.push_back(new GameObject(*groundPrefab));

	playingLayer->Submit(background); //TODO change submit to priority or add order in layer to sprite
	playingLayer->Submit(grounds[0]);
	playingLayer->Submit(bird);

	//bird->GetTransform().Rotate(Quaternion(0.0f, 0.0f, -91.0f)); //TEMP!!!!
	//PRIME_INFO(bird->GetTransform().GetRotation().EulerAngles().z * (180.0f / PI), "\n"); //TEMP!!
	//SpawnGround(); //temp
}

void FlappyBird::Update()
{
	SpawnGround();
	SpawnPipes();
	//PRIME_INFO(GetFPS(), "fps \n");
	if (InputPC::GetKeyDown(32))
	{
		//TODO should be some kind of animation
		//bird->GetTransform().SetPosition(bird->GetTransform().GetPosition() + Vector3::up() * 200.0f);
		std::thread jumpAnim(&FlappyBird::Jump, this, 175.0f);
		jumpAnim.detach();
	}

	bird->GetTransform().Position = bird->GetTransform().Position + Vector3::right() * GetDeltaTime() * 150.0f;
	background->GetTransform().Position.x = bird->GetTransform().Position.x;
	Gravity(*bird);
}

void FlappyBird::Tick()
{
	PRIME_INFO("////////////////////////////////////////////////////////////////\n");
	PRIME_INFO("Grounds size: ", grounds.size(), "\n");
	PRIME_INFO("Pipes size: ", pipes.size(), "\n");
	PRIME_INFO(GetFPS(), "fps \n");
	float width = groundPrefab->GetComponent<Sprite>()->GetSize().x;
	PRIME_INFO("Camera: ", mainCamera->ScreenToWorldPoint(InputPC::GetMousePosition()), "\n");
	PRIME_INFO("Brid position: ", bird->GetTransform().Position, "\n");
	PRIME_INFO("////////////////////////////////////////////////////////////////\n");
}

void FlappyBird::Render()
{
	mainCamera->SetPosition(Vector2(bird->GetTransform().Position.x, mainCamera->GetPosition().y));
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back()); //TODO move this to engine
	playingLayer->Render();
}