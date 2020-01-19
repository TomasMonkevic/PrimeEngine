#define P_LOG_LEVEL 0

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
#define BIRD_COLLISION_RADIUS 30.5f

#define GRAVITY 23.0f

namespace {
    bool AreColliding(const Vector3& circlePos, float radius, const Vector3& rectPos, const Sprite& rect) {
        float x1 = rectPos.x - rect.GetSize().x / 2.0f;
        float x2 = rectPos.x + rect.GetSize().x / 2.0f;
        float y1 = rectPos.y - rect.GetSize().y / 2.0f;
        float y2 = rectPos.y + rect.GetSize().y / 2.0f;
        return x1 - radius < circlePos.x && circlePos.x < x2 + radius &&
                y1 - radius < circlePos.y && circlePos.y < y2 + radius;
    }
}

FlappyBird::~FlappyBird()
{
	delete playingLayer;
	delete mainCamera;
	delete bird;
	delete background;
	delete groundPrefab;
	delete pipeBottomPrefab;
	delete pipeTopPrefab;
	delete arial;
}

void FlappyBird::Destroy(GameObject* obj)
{
	playingLayer->Remove(obj);
	delete obj;
}

bool FlappyBird::DidBirdCollide() {
	Vector3 birdPosition = bird->GetTransform().Position;
	for(const auto* pipe : pipes) {
		if(AreColliding(birdPosition, BIRD_COLLISION_RADIUS, pipe->GetTransform().Position, *pipe->GetComponent<Sprite>())) {
			PRIME_INFO("Collision with pipe");
			return true;
		}
	}
	for(const auto* ground : grounds) {
		if(AreColliding(birdPosition, BIRD_COLLISION_RADIUS, ground->GetTransform().Position, *ground->GetComponent<Sprite>())) {
			PRIME_INFO("Collision with ground");
			return true;
		}
	}
	return false;
}

void FlappyBird::Gravity(GameObject& obj)
{
	Sprite* sprite = groundPrefab->GetComponent<Sprite>();
	float groundY = groundPrefab->GetTransform().Position.y + sprite->GetSize().y / 2.0f + obj.GetComponent<Sprite>()->GetSize().y / 2.0f;

	//Velocity
	birdVelocity.y -= GRAVITY * GetDeltaTime();
	obj.GetTransform().Position += birdVelocity * BIRD_MASS * GetDeltaTime();

	obj.GetTransform().Position.y = std::min(mainCamera->ViewportToWorldPoint(Vector2(0.0f, 1.0f)).y,
			std::max(groundY, obj.GetTransform().Position.y));
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

void FlappyBird::RestartGame() {
    bird->GetTransform().Position.y = 0;
    bird->GetTransform().Rotation = Math::Quaternion::identity();
    while(!pipes.empty()) {
        playingLayer->Remove(pipes.back());
        delete pipes.back();
        pipes.pop_back();
    }
	birdVelocity = Vector2::zero();
    angularMomentum = 0.0f;
    birdRotation = 0.0f;
    isGameOver_ = false;
    isGameStarted_ = false;
}

void FlappyBird::SpawnPipes()
{
	int random = rand() % PIPE_MAX_Y + PIPE_MIN_Y;
	float posY = mainCamera->ViewportToWorldPoint(Vector2(1.0f, -1.0f)).y + random; //+random pos
	float width = pipeBottomPrefab->GetComponent<Sprite>()->GetSize().x;

	if (pipes.empty() || mainCamera->WorldToViewPoint(pipes.back()->GetTransform().Position - Vector2(width / 2.0f, 0.0f)).x <= 1.0f)
	{
		PRIME_INFO("Pipe spawned! \n");
		pipes.push_back(new GameObject(*pipeBottomPrefab));
		pipes.back()->GetTransform().Position.x = nextPipePosition;
		pipes.back()->GetTransform().Position.y = posY;

		pipes.push_back(new GameObject(*pipeTopPrefab));
		pipes.back()->GetTransform().Position.x = nextPipePosition;
		pipes.back()->GetTransform().Position.y = posY + PIPE_GAP;

		playingLayer->Submit(pipes[pipes.size() - 1]);
		playingLayer->Submit(pipes[pipes.size() - 2]);
		nextPipePosition += PIPE_SPREAD;
	}

	if (!pipes.empty() && mainCamera->WorldToViewPoint(pipes[0]->GetTransform().Position + Vector2(width / 2.0f, 0.0f)).x <= -2.0f)
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
	//CreateWin("Flappy Bird", 1080, 2280);
    CreateWin("Flappy Bird", 720, 1280);
	GetWindow()->EnableVSync(true);
	//GetWindow()->SetColor(Color(84, 192, 201));

	//TODO make a main camera in gameLayer or return a handle to camera; think about the camera system
	mainCamera = new Camera(Matrix4x4::Orthographic(-360.0f, 360.0f, -640.0f, 640.0f, -1.0f, 1.0f));
	playingLayer = new GameLayer(ShaderManagerI.CreateShader("mainShader", Shader::defaultShader), mainCamera);
	//TODO make an error log if existing shader name is used
	uiLayer = new UILayer();

	float scale = 5.0f; //5.0f

	bird = new GameObject();
	bird->AddComponent(new Sprite(Vector2(17.0f, 12.0f) * scale, "Textures/bird1.png")); //TODO think about scale and sprite size
	bird->Priority = 5;

	background = new GameObject(Vector2(0.0f, 0.0f)); 
	background->AddComponent(new Sprite(Vector2(144.0f, 256.0f) * scale, "Textures/dayBg.png"));
	background->Priority = 0;

	groundPrefab = new GameObject(Vector2(0.0f, -499.0f)); //TODO remove hardcoded values
	groundPrefab->Priority = 10;
	groundPrefab->AddComponent(new Sprite(Vector2(168.0f, 56.0f) * scale, "Textures/ground.png"));

	//TODO nest two pipes in one gameOjbect
	//move childs to transform and make local and world position/rotation/scale
	pipeBottomPrefab = new GameObject(Vector2(0.0f, 100.0f));
	pipeBottomPrefab->AddComponent(new Sprite(Vector2(26.0f, 160.0f) * scale, "Textures/pipeBottom.png"));
	pipeBottomPrefab->Priority = 2;

	pipeTopPrefab = new GameObject(Vector2(0.0f, -100.0f));
	pipeTopPrefab->AddComponent(new Sprite(Vector2(26.0f, 160.0f) * scale, "Textures/pipeTop.png"));
	pipeTopPrefab->Priority = 2;

	grounds.push_back(new GameObject(*groundPrefab));

	//score text
	arial = new Font("Fonts/arial.ttf", Color(1.0f, 0.0f, 0.0f), 64);
	score = new GameObject(Vector2(0.0f, 1.0f));
	score->AddComponent(new Label("Hello\nnew line", *arial));
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
	//PRIME_INFO(GetFPS(), "fps \n");
	//if (InputPC::GetKeyDown(32) || InputPC::GetMouseButtonDown(0))
	auto touches = InputPC::GetTouches();
	if (touches.size() == 1 && touches[0].phase == Input::TouchPhase::BEGAN)
	{
	    if(isGameOver_) {
            RestartGame();
            return;
	    }
	    else {
            //TODO should be some kind of animation
            isGameStarted_ = true;
            birdVelocity.y = BIRD_JUMP_HEIGHT;
            angularMomentum = BIRD_JUMP_ROTATION_SPEED;
	    }
	}

    SpawnGround();
    if(isGameStarted_) {
        Gravity(*bird);
        SpawnPipes();
        if(DidBirdCollide()) {
            isGameOver_ = true;
        }
    }
    else {
        nextPipePosition = mainCamera->ViewportToWorldPoint(Vector2(1.0f, 0.0f)).x + PIPE_DELAY;
    }
    if(!isGameOver_) {
		bird->GetTransform().Position.x += GetDeltaTime() * BIRD_MOVEMENT_SPEED;
	}
	background->GetTransform().Position.x = bird->GetTransform().Position.x;
    mainCamera->GetTransform().Position.x = bird->GetTransform().Position.x;
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
	playingLayer->Render();
	uiLayer->Render();
}