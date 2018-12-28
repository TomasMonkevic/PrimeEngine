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
	//GetWindow()->SetColor(Color(0.5f, 0.5f, 0.5f, 1.0f));
	GetWindow()->SetColor(Color(0xfff48642));

	//Matrix4x4 pr = Matrix4x4::Orthographic(0.0f, 16.0f, -4.50f, 4.50f, -50.0f, 50.0f);
	const Matrix4x4 pr = Matrix4x4::Perspective(90.0f, 16.0f / 9.0f, 0.1f, 500.0f);

	mainCamera = new Camera(pr);

	Vector3 cameraPosition(Vector3(0.0f, 0.0f, -10.0f)); //projection
	//Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->GetTransform().Position = cameraPosition;
	mainCamera->AddComponent(new FpsCamera(7.0f, Vector2(0.015f, 0.015f)));

	player = new GameObject();
	//player->AddComponent(new Sprite (Vector2(17, 12) / 5, "Resources\\Textures\\bird1.png"));
	Material* boxMaterial = new Material(Shader::phong, new Texture("Resources/Textures/boxDiff.png"), new Texture("Resources/Textures/boxSpec.png")); //TODO don't forget to delete this
	player->AddComponent(new MeshRenderer(Mesh::Cube(Color::White()), boxMaterial));

	GameObject* cube2 = new GameObject();
	//TODO test what happens when copyed?
	//TODO reuse same geometry/mesh
	Material* brickMaterial = new Material(Shader::phong, new Texture("Resources/Textures/bird1.png"));
	brickMaterial->NormalMap(new Texture("Resources/Textures/brickwall_normal.jpg"));
	brickMaterial->Smoothness() = 1024;
	cube2->AddComponent(new MeshRenderer(Mesh::Cube(Color(1.0f, 0.8f, 0.0f)), brickMaterial));
	cube2->GetTransform().Position.x = 5.0f;

	GameObject* ground = new GameObject(Vector3(0.0f, -1.0f, 0.0f));
	Material* groundMaterial = new Material(Shader::phong); //TODO also memory leak
	groundMaterial->Smoothness() = 256.0f;
	ground->AddComponent(new MeshRenderer(Mesh::Cube(Color::White(), 100.0f, 0.1f, 100.0f), groundMaterial)); 

	//light->AddComponent(new MeshRenderer(Mesh::Cube(Color::White(), 0.1f, 0.1f, 0.1f), new Material(Shader::glow))); //TODO only temp
	PointLight* light = new PointLight(Color::White(), 0.7f, 25.0f);
	light->GetTransform().Position = Vector3(5.0f, 5.0f, 2.0f);

	PointLight* light2 = new PointLight(Color(1.0, 0.1, 0.0f), 0.7f, 25.0f);
	light2->GetTransform().Position = Vector3(-5.0f, 2.0f, 2.0f);

	AmbientLight* ambientLight = new AmbientLight(Color::White(), 0.35f);

	sun = new DirectionalLight(Color(0xffbafbfc), 0.7f);
	flashLight = new SpotLight(Color(0xffbafbfc), 0.7f, 15.0f, 20.0f, 15.0f);

	//GameObject* loadedModel = GameObject::LoadObjModel("Resources/Models/katilas.obj", true);

	mainScene = new Scene(mainCamera);
	//mainScene->Add(loadedModel);
	mainScene->Add(player);
	mainScene->Add(cube2);
	mainScene->Add(ground);
	mainScene->Add(light);
	mainScene->Add(light2);
	mainScene->Add(sun);
	mainScene->Add(ambientLight);
	mainScene->Add(flashLight);
}

void TestGame::Update()
{
	//TODO could be called automaticaly when scene is implemented
	player->GetTransform().Rotate(Quaternion::Rotation(GetDeltaTime() * 0.5f, Vector3::up()));
	sun->GetTransform().Rotate(Quaternion::Rotation(GetDeltaTime() * 0.1f, Vector3::right()));
	mainCamera->GetComponent<FpsCamera>()->Update(GetDeltaTime());

	flashLight->GetTransform().Position = mainCamera->GetTransform().Position;
	flashLight->GetTransform().Rotation = mainCamera->GetTransform().Rotation;
	if (InputPC::GetKeyDown(256)) //esc
	{
		GetWindow()->Close();
	}
}

void TestGame::Tick()
{
	PRIME_INFO(GetFPS(), " fps \n");
	PRIME_INFO(mainCamera->GetTransform().Position, '\n');
}

void TestGame::Render()
{
	mainScene->Render();
}