#define P_LOG_LEVEL 2

#include "Demo.h"
#include <time.h>

void Demo::Awake()
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	CreateWin("PE|3D Demo", 1366, 768);
	//CreateWin("PE|3D Demo");
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Color(0xfff48642));

	const Matrix4x4 pr = Matrix4x4::Perspective(60.0f, 16.0f / 9.0f, 0.3f, 1000.0f);

	mainCamera = new Camera(ShaderManagerI.CreateShader("gameShader", Shader::phong), pr);
	mainCamera->GetTransform().Position = Vector3(-1.76f, 13.62f, -11.3f);
	mainCamera->GetTransform().Rotation = Quaternion(50.0f, -30.0f, 0.0f);
	mainCamera->AddComponent(new FpsCamera(20.0f, Vector2(0.015f, 0.015f)));

	GameObject* ground = new GameObject(Vector3(0.0f, 0.0f, 0.0f));
	Material* groundMaterial = new Material(Shader::phong); //TODO also memory leak
	groundMaterial->Smoothness() = 256.0f;
	groundMaterial->DiffuseColor() = Color(0xFF317184);
	ground->AddComponent(new MeshRenderer(Mesh::Cube(Color::white, 1000.0f, 0.1f, 1000.0f), groundMaterial));

	AmbientLight* ambientLight = new AmbientLight(Color::white, 0.35f);

	sun = new DirectionalLight(Color(0xffd6f4ff), 1.0f);
	//sun->GetTransform().Rotation = Quaternion(50.0f, -30.0f, 0.0f);

	ModelImporter objModelImporter;

	Material* floorMaterial = new Material(Shader::phong,
		new Texture("Resources/SpecialScene/Textures/FloorCircular01_Albedo.png"));
		//new Texture("Resources/SpecialScene/Textures/FloorCircular01_MetallicSmooth.png"));
	//floorMaterial->NormalMap(new Texture("Resources/SpecialScene/Textures/FloorCircular01_Normal.png"));
	GameObject* floorCircular = new GameObject;
	floorCircular->AddComponent(new MeshRenderer(objModelImporter.ImportModel("Resources/SpecialScene/Models/FloorCircular01.obj", true), floorMaterial));
	floorCircular->GetTransform().Position = Vector3(-7.58f, 0.97f, -0.855f);
	floorCircular->GetTransform().Scale *= 0.01f;

	Material* alienStatueMaterial = new Material(Shader::phong,
		new Texture("Resources/SpecialScene/Textures/Statue_Albedo.png"));
		//new Texture("Resources/SpecialScene/Textures/Statue_MetallicSmooth.png"));
	//alienStatueMaterial->NormalMap(new Texture("Resources/SpecialScene/Textures/Statue_Normal.png"));
	GameObject* alienStatue = new GameObject;
	alienStatue->AddComponent(new MeshRenderer(objModelImporter.ImportModel("Resources/SpecialScene/Models/AlienStatue.obj", true), alienStatueMaterial));
	alienStatue->GetTransform().Position = Vector3(-7.58f, 1.57f, -0.855f);
	alienStatue->GetTransform().Rotation = Quaternion(0.0f, 102.2f, 0.0f);
	alienStatue->GetTransform().Scale *= 0.1f;

	//GameObject* gates = GameObject::LoadObjModel("Resources/SpecialScene/Models/GateHuge01.obj", true);
	//gates->GetTransform().Position = Vector3(17.97f, 0.13f, -2.855f);
	//gates->GetTransform().Rotation = Quaternion(0.0f, -82.3f, 0.0f);
	//gates->GetTransform().Scale *= 0.2f;

	//GameObject* rock01 = GameObject::LoadObjModel("Resources/SpecialScene/Models/RockChunk01.obj", true);
	//rock01->GetTransform().Position = Vector3(8.84f, 1.68f, 21.47f);
	//rock01->GetTransform().Rotation = Quaternion(0.0f, -51.933f, 0.0f);
	//rock01->GetTransform().Scale *= 0.1f;

	flashLight = new SpotLight(Color(0xffbafbfc), 0.7f, 15.0f, 50.0f, 15.0f);

	mainScene = new Scene(mainCamera);
	//mainScene->Add(rock01);
	mainScene->Add(alienStatue);
	//mainScene->Add(gates);
	mainScene->Add(ground);
	mainScene->Add(floorCircular);
	mainScene->Add(sun);
	mainScene->Add(ambientLight);

	mainScene->Add(flashLight);
}

void Demo::Update()
{
	mainCamera->GetComponent<FpsCamera>()->Update(GetDeltaTime());
	sun->GetTransform().Rotate(Quaternion::Rotation(GetDeltaTime() * 0.1f, Vector3::right()));

	flashLight->GetTransform().Position = mainCamera->GetTransform().Position;
	flashLight->GetTransform().Rotation = mainCamera->GetTransform().Rotation;

	if (InputPC::GetKeyDown(256)) //esc
	{
		GetWindow()->Close();
	}
}

void Demo::Tick()
{
	PRIME_INFO(GetFPS(), " fps \n");
}

void Demo::Render()
{
	mainCamera->Render();
	mainScene->Render();
}