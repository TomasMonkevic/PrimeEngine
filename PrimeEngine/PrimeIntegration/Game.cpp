#define P_LOG_LEVEL 2

#include "Game.h"
#include <time.h>

void TestGame::Awake()
{
	//make a method in the engine?
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	CreateWin("3D Rendering test", 1366, 768);
	//CreateWin("3D Rendering test");
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

	//Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

	mainCamera = new Camera(ShaderManagerI.CreateShader("gameShader", Shader::phong), pr);

	Vector3 cameraPosition(Vector3(0.0f, 0.0f, -10.0f)); //projection
	//Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->GetTransform().Position = cameraPosition;
	mainCamera->AddComponent(new FpsCamera());

	//gameLayer = new GameLayer(mainCamera);

	player = new GameObject();
	//player->AddComponent(new Sprite (Vector2(17, 12) / 5, "Resources\\Textures\\bird1.png"));
	player->AddComponent(new MeshRenderer(Mesh::Cube(), ShaderManagerI.CreateShader("cubeShader", Shader::phong)));
	//gameLayer->Submit(player);
	//cube = Mesh::Cube();
}

void TestGame::Update()
{
	//TODO could be called automaticaly when scene is implemented
	player->GetTransform().Rotate(Quaternion::Rotation(GetDeltaTime() * 3.0f, Vector3::up()));
	mainCamera->GetComponent<FpsCamera>()->Update(GetDeltaTime());
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
	//gameLayer->Render();
	player->GetComponent<MeshRenderer>()->Draw(*mainCamera);
}