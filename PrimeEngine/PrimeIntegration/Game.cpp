#define P_LOG_LEVEL 2

#include "Game.h"
#include <time.h>

void TestGame::Awake()
{
	//make a method in the engine?
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	//CreateWin("Tik Tac Toe", 1366, 768);
	CreateWin("Test Game", 800, 600);
	//CreateWin("PrimeEngine");
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Color(0.7f, 0.8f, 1.0f, 1.0f));

	//Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

	mainCamera = new Camera(ShaderManagerI.CreateShader("gameShader", Shader::default), pr);

	Vector3 cameraPosition(Vector3(0.0f, 0.0f, -10.0f)); //projection
	//Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->GetTransform().Position = cameraPosition;
	//mainCamera->LookAt(mainCamera->GetTransform().Position + Vector3::forward());

	gameLayer = new GameLayer(mainCamera);

	player = new GameObject();
	player->AddComponent(new Sprite (Vector2(17, 12) / 5, "Resources\\Textures\\bird1.png"));
	gameLayer->Submit(player);
}

void TestGame::Update()
{
	float cameraSpeed = 10.0f;
	if (InputPC::GetKey('A'))
	{
		mainCamera->GetTransform().Position.x -= cameraSpeed * GetDeltaTime();
	}
	else if (InputPC::GetKey('D'))
	{
		mainCamera->GetTransform().Position.x += cameraSpeed * GetDeltaTime();
	}
	if (InputPC::GetKey('W'))
	{
		mainCamera->GetTransform().Position.z += cameraSpeed * GetDeltaTime();
	}
	else if (InputPC::GetKey('S'))
	{
		mainCamera->GetTransform().Position.z -= cameraSpeed * GetDeltaTime();
	}
	if (InputPC::GetKey('Q'))
	{
		mainCamera->GetTransform().Position.y += cameraSpeed * GetDeltaTime();
	}
	else if (InputPC::GetKey('E'))
	{
		mainCamera->GetTransform().Position.y -= cameraSpeed * GetDeltaTime();
	}
	static Vector2 pervMousePos;
	Vector2 deltaMouse = InputPC::GetMousePosition() - pervMousePos;
	Vector2 mouseSensitivity(0.015f, 0.015f);
	mainCamera->GetTransform().Rotate(Quaternion::Rotation(deltaMouse.y * mouseSensitivity.y, Vector3::right())
	* Quaternion::Rotation(deltaMouse.x * mouseSensitivity.x, Vector3::up()));
	mainCamera->GetTransform().Rotation.z = 0; //TODO why should I clear this?????
	Vector3 eulerRotation = mainCamera->GetTransform().Rotation.EulerAngles();
	//PRIME_INFO(ToDegrees(eulerRotation.x)," ", ToDegrees(eulerRotation.y), " ", ToDegrees(eulerRotation.z), '\n');
	//mouseSensitivity *= 10.0f;
	//eulerRotation.x += deltaMouse.y * mouseSensitivity.y;
	//mainCamera->GetTransform().Rotation = Quaternion(eulerRotation.x, eulerRotation.y, eulerRotation.z); //TODO make constructor from vec3
	//PRIME_INFO(mainCamera->GetTransform().Rotation, '\n');
	pervMousePos = InputPC::GetMousePosition();

	if (InputPC::GetKeyDown(256)) //esc
	{
		GetWindow()->Close();
	}
}

void TestGame::Tick()
{
	PRIME_INFO(GetFPS(), " fps \n");
}

void TestGame::Render()
{
	mainCamera->Render();
	gameLayer->Render();
}