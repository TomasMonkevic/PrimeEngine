#define P_LOG_LEVEL 2

#include "Game.h"
#include <time.h>
#include <Input.h>

void TestGame::Awake()
{
	//make a method in the engine?
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	CreateWin("3D Rendering test", 2200, 1080);
	//CreateWin("3D Rendering test");
	GetWindow()->EnableVSync(true);
	//GetWindow()->SetColor(Color(0.5f, 0.5f, 0.5f, 1.0f));
	GetWindow()->SetColor(Color(0xfff48642));

	//Matrix4x4 pr = Matrix4x4::Orthographic(0.0f, 16.0f, -4.50f, 4.50f, -50.0f, 50.0f);
	const Matrix4x4 pr = Matrix4x4::Perspective(90.0f, 16.0f / 9.0f, 0.1f, 500.0f);

	mainCamera = new Camera(pr);

	Vector3 cameraPosition(Vector3(0.0f, 0.0f, -2.0f)); //projection
	//Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->GetTransform().Position = cameraPosition;
	mainCamera->AddComponent(new FpsCamera(7.0f, Vector2(0.015f, 0.015f)));

	player = new GameObject();
	Material* boxMaterial = new Material(Shader::phong, Color::Blue()); //TODO don't forget to delete this
	player->AddComponent(new MeshRenderer(Mesh::Cube(Color::White()), boxMaterial));

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

	mainScene = new Scene(mainCamera);
	//mainScene->Add(loadedModel);
	mainScene->Add(player);
	mainScene->Add(ground);
	mainScene->Add(light);
	mainScene->Add(light2);
	mainScene->Add(sun);
	mainScene->Add(ambientLight);
}

void TestGame::Update()
{
	//TODO could be called automaticaly when scene is implemented
	player->GetTransform().Rotate(Quaternion::Rotation(GetDeltaTime() * 0.5f, Vector3::up()));
	sun->GetTransform().Rotate(Quaternion::Rotation(GetDeltaTime() * 0.1f, Vector3::right()));
	PRIME_INFO("Touch count: ", Input::InputPC::GetTouchCount());
	std::vector<Input::Touch> touches = Input::InputPC::GetTouches();
	for(int i=0; i<touches.size(); i++) {
	    PRIME_INFO(i, " ", touches[i].fingerId, " Delta: ", touches[i].deltaPosition, " Pos: ", touches[i].position);
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