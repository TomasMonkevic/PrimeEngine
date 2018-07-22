#define P_LOG_LEVEL 2

#include "FlappyBird.h"

#include <ctime>
#include <algorithm>

#define PIPE_GAP 1012.5f
#define PIPE_SPREAD 385.0f
#define PIPE_DELAY 500.0f
#define PIPE_MIN_Y 0
#define PIPE_MAX_Y  350

#define BIRD_MASS 83.0f
#define BIRD_MOVEMENT_SPEED 280.5f //170?? //3.5 BL?
#define BIRD_ROTATION_SPEED 1400.0f
#define BIRD_JUMP_ROTATION_SPEED -700.0f
#define BIRD_JUMP_HEIGHT 8.5f

#define GRAVITY 23.0f

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

void FlappyBird::Destroy(GameObject* obj)
{
	playingLayer->Remove(obj);
	delete obj;
}

void FlappyBird::Gravity(GameObject& obj)
{
	Sprite* sprite = groundPrefab->GetComponent<Sprite>();
	float groundY = groundPrefab->GetTransform().Position.y + sprite->GetSize().y / 2.0f + obj.GetComponent<Sprite>()->GetSize().y / 2.0f;

	//Velocity
	birdVelocity.y -= GRAVITY * GetDeltaTime();
	obj.GetTransform().Position += birdVelocity * BIRD_MASS * GetDeltaTime();

	obj.GetTransform().Position.y = std::max(groundY, obj.GetTransform().Position.y);
	birdVelocity.y = std::max(groundY, birdVelocity.y);

	//Rotation
	angularMomentum += BIRD_ROTATION_SPEED * GetDeltaTime();
	birdRotation -= angularMomentum * GetDeltaTime();

	birdRotation = std::max(-90.0f, birdRotation);
	birdRotation = std::min(20.0f, birdRotation);

	angularMomentum = std::max(-600.0f, angularMomentum);
	angularMomentum = std::min(800.0f, angularMomentum);

	obj.GetTransform().Rotation = Quaternion(0.0f, 0.0f, birdRotation);
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
		Destroy(grounds[0]);
		grounds.erase(grounds.begin());
		//TODO deep copy all pointers in component system
	}
}

void FlappyBird::SpawnPipes()
{
	float initialPos = mainCamera->ViewportToWorldPoint(Vector2(1.0f, 0.0f)).x + PIPE_DELAY;
	int random = rand() % PIPE_MAX_Y + PIPE_MIN_Y;
	float posY = mainCamera->ViewportToWorldPoint(Vector2(1.0f, -1.0f)).y + random; //+random pos
	static float nextPipePosition = initialPos;
	float width = pipeBottomPrefab->GetComponent<Sprite>()->GetSize().x; 

	if (nextPipePosition == initialPos)
	{
		pipes.push_back(new GameObject(*pipeBottomPrefab));
		pipes.back()->GetTransform().Position.x = nextPipePosition;
		pipes.back()->GetTransform().Position.y = posY;

		pipes.push_back(new GameObject(*pipeTopPrefab));
		pipes.back()->GetTransform().Position.x = nextPipePosition;
		pipes.back()->GetTransform().Position.y = posY + PIPE_GAP;
	}

	if (mainCamera->WorldToViewPoint(pipes.back()->GetTransform().Position - Vector2(width / 2.0f, 0.0f)).x <= 1.0f)
	{
		PRIME_INFO("Pipe spawned! \n");
		playingLayer->Submit(pipes[pipes.size() - 1]);
		playingLayer->Submit(pipes[pipes.size() - 2]);
		nextPipePosition += PIPE_SPREAD;

		if (nextPipePosition != initialPos)
		{
			pipes.push_back(new GameObject(*pipeBottomPrefab));
			pipes.back()->GetTransform().Position.x = nextPipePosition;
			pipes.back()->GetTransform().Position.y = posY;

			pipes.push_back(new GameObject(*pipeTopPrefab));
			pipes.back()->GetTransform().Position.x = nextPipePosition;
			pipes.back()->GetTransform().Position.y = posY + PIPE_GAP;
		}
	}

	if (mainCamera->WorldToViewPoint(pipes[0]->GetTransform().Position + Vector2(width / 2.0f, 0.0f)).x <= -2.0f)
	{
		PRIME_INFO("Pipes deleted \n");
		playingLayer->Remove(pipes[0]);
		playingLayer->Remove(pipes[1]);
		delete pipes[0];
		delete pipes[1];
		pipes.erase(pipes.begin());
		pipes.erase(pipes.begin());
		//TODO deep copy all pointers in component system
	}
}

void FlappyBird::Awake()
{
	//Windows setup
	CreateWin("Flappy Bird", 720, 1280);
	GetWindow()->EnableVSync(false);
	//GetWindow()->SetColor(Color(84, 192, 201));

	//TODO make a main camera in gameLayer or return a handle to camera; think about the camera system
	mainCamera = new Camera(Matrix4x4::Orthographic(-360.0f, 360.0f, -640.0f, 640.0f, -1.0f, 1.0f));
	playingLayer = new GameLayer(ShaderManagerI.CreateShader("mainShader", Shader::defaultShader), mainCamera);
	//TODO make an error log if existing shader name is used
	uiLayer = new UILayer();

	float scale = 5.0f; //5.0f

	bird = new GameObject();
	bird->AddComponent(new Sprite(Vector2(17.0f, 12.0f) * scale, "Resources\\Textures\\bird1.png")); //TODO think about scale and sprite size
	bird->Priority = 5;

	background = new GameObject(Vector2(0.0f, 0.0f)); 
	background->AddComponent(new Sprite(Vector2(144.0f, 256.0f) * scale, "Resources\\Textures\\dayBg.png"));
	background->Priority = 0;

	groundPrefab = new GameObject(Vector2(0.0f, -499.0f)); //TODO remove hardcoded values
	groundPrefab->Priority = 10;
	groundPrefab->AddComponent(new Sprite(Vector2(168.0f, 56.0f) * scale, "Resources\\Textures\\ground.png"));

	//TODO nest two pipes in one gameOjbect
	//move childs to transform and make local and world position/rotation/scale
	pipeBottomPrefab = new GameObject(Vector2(0.0f, 100.0f));
	pipeBottomPrefab->AddComponent(new Sprite(Vector2(26.0f, 160.0f) * scale, "Resources\\Textures\\pipeBottom.png"));
	pipeBottomPrefab->Priority = 2;

	pipeTopPrefab = new GameObject(Vector2(0.0f, -100.0f));
	pipeTopPrefab->AddComponent(new Sprite(Vector2(26.0f, 160.0f) * scale, "Resources\\Textures\\pipeTop.png"));
	pipeTopPrefab->Priority = 2;

	grounds.push_back(new GameObject(*groundPrefab));

	//score text
	score = new Text("Hello\nNewLine", arial);
	uiLayer->Submit(score);

	//why doesn't it wokk if bg is first?
	playingLayer->Submit(grounds[0]);
	playingLayer->Submit(background); //TODO change submit to priority or add order in layer to sprite
	playingLayer->Submit(bird);

	//bird->GetTransform().Rotate(Quaternion(0.0f, 0.0f, -91.0f)); //TEMP!!!!
	//PRIME_INFO(bird->GetTransform().GetRotation().EulerAngles().z * (180.0f / PI), "\n"); //TEMP!!
	srand(time(0));
}

void FlappyBird::Update()
{
	SpawnGround();
	SpawnPipes();
	//PRIME_INFO(GetFPS(), "fps \n");
	if (InputPC::GetKeyDown(32) || InputPC::GetMouseButtonDown(0))
	{
		//TODO should be some kind of animation
		birdVelocity.y = BIRD_JUMP_HEIGHT;
		angularMomentum = BIRD_JUMP_ROTATION_SPEED;
	}

	bird->GetTransform().Position.x += GetDeltaTime() * BIRD_MOVEMENT_SPEED;
	background->GetTransform().Position.x = bird->GetTransform().Position.x;
	Gravity(*bird);
}

void FlappyBird::Tick()
{
	PRIME_INFO("////////////////////////////////////////////////////////////////\n");
	PRIME_INFO("Grounds size: ", grounds.size(), "\n");
	PRIME_INFO("Pipes size: ", pipes.size(), "\n");
	PRIME_WARNING(GetFPS(), "fps \n");
	PRIME_INFO("Camera: ", mainCamera->ScreenToWorldPoint(InputPC::GetMousePosition()), "\n");
	PRIME_INFO("Brid position: ", bird->GetTransform().Position, "\n");
	PRIME_INFO("////////////////////////////////////////////////////////////////\n");
}

void FlappyBird::Render()
{
	mainCamera->GetTransform().Position.x = bird->GetTransform().Position.x;
	playingLayer->Render();
	uiLayer->Render();
}