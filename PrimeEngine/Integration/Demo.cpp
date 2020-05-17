#define P_LOG_LEVEL 2

#include "Demo.h"
#include <time.h>

void Demo::Awake()
{
#ifndef PE_ANDROID
	GetWindow()->SetTitle("PE|3D Demo");
	GetWindow()->EnableVSync(true);
#endif
	GetWindow()->SetSize(1366, 768);
	GetWindow()->SetColor(Color(0xfff48642));
	GetWindow()->Initialize();

	mainCamera = new Camera(Matrix4x4::Perspective(60.0f, 16.0f / 9.0f, 0.3f, 1000.0f));
	mainCamera->GetTransform().Position = Vector3(-1.76f, 13.62f, -11.3f);
	mainCamera->GetTransform().Rotation = Quaternion(50.0f, -30.0f, 0.0f);
	mainCamera->AddComponent(new FpsCamera(20.0f, Vector2(0.015f, 0.015f)));

	GameObject* ground = new GameObject(Vector3(0.0f, 0.0f, 0.0f));
	Material* groundMaterial = new Material(Shader::phong); //TODO also memory leak
	groundMaterial->Smoothness() = 256.0f;
	groundMaterial->DiffuseColor() = Color(0xFF317184);
	ground->AddComponent(new MeshRenderer(Mesh::Cube(Color::White(), 1000.0f, 0.1f, 1000.0f), groundMaterial));

	AmbientLight* ambientLight = new AmbientLight(Color(0xff9a9a9a), 0.75f);

	sun = new DirectionalLight(Color(0xffd6f4ff), 1.0f);
	//sun->GetTransform().Rotation = Quaternion(50.0f, -30.0f, 0.0f);

	ModelImporter objModelImporter;

	Material* floorMaterial = new Material(Shader::phong,
		new Texture("Resources/SpecialScene/Textures/FloorCircular01_Albedo.png"),
		new Texture("Resources/SpecialScene/Textures/FloorCircular01_MetallicSmooth.png"));
	floorMaterial->NormalMap(new Texture("Resources/SpecialScene/Textures/FloorCircular01_Normal.png"));
	GameObject* floorCircular = new GameObject;
	floorCircular->AddComponent(new MeshRenderer(objModelImporter.ImportModel("Resources/SpecialScene/Models/FloorCircular01.obj", true), floorMaterial));
	floorCircular->GetTransform().Position = Vector3(-6.58f, 0.97f, -2.855f);
	floorCircular->GetTransform().Scale *= 0.01f;

	Material* alienStatueMaterial = new Material(Shader::phong,
		new Texture("Resources/SpecialScene/Textures/Statue_Albedo.png"),
	new Texture("Resources/SpecialScene/Textures/Statue_MetallicSmooth.png"));
	alienStatueMaterial->NormalMap(new Texture("Resources/SpecialScene/Textures/Statue_Normal.png"));
	alienStatue = new GameObject;
	alienStatue->AddComponent(new MeshRenderer(objModelImporter.ImportModel("Resources/SpecialScene/Models/AlienStatue.obj", true), alienStatueMaterial));
	alienStatue->GetTransform().Position = Vector3(-6.58f, 1.0f, -2.855f);
	alienStatue->GetTransform().Rotation = Quaternion(0.0f, 102.2f, 0.0f);
	alienStatue->GetTransform().Scale *= 0.1f;

	Material* gatesMaterial = new Material(Shader::phong,
		new Texture("Resources/SpecialScene/Textures/GateHuge01_Albedo.png"),
		new Texture("Resources/SpecialScene/Textures/GateHuge01_MetallicSmooth.png"));
	gatesMaterial->NormalMap(new Texture("Resources/SpecialScene/Textures/GateHuge01_Normal.png"));
	GameObject* gates = new GameObject;
	gates->AddComponent(new MeshRenderer(objModelImporter.ImportModel("Resources/SpecialScene/Models/GateHuge01.obj", true), gatesMaterial));
	gates->GetTransform().Position = Vector3(17.97f, 0.13f, -2.855f);
	gates->GetTransform().Rotation = Quaternion(0.0f, -82.3f, 0.0f);
	gates->GetTransform().Scale *= 0.2f;

	Mesh* rockMesh = objModelImporter.ImportModel("Resources/SpecialScene/Models/RockChunk01.obj", true);
	Material* rocksMaterial = new Material(Shader::phong,
		new Texture("Resources/SpecialScene/Textures/RockChunk01_Albedo.png"),
		new Texture("Resources/SpecialScene/Textures/RockChunk01_MetallicSmooth.png"));
	rocksMaterial->NormalMap(new Texture("Resources/SpecialScene/Textures/RockChunk01_Normal.png"));
	GameObject* rock01 = new GameObject;
	rock01->AddComponent(new MeshRenderer(rockMesh, rocksMaterial));
	rock01->GetTransform().Position = Vector3(8.84f, 0.0f, 15.47f);
	rock01->GetTransform().Rotation = Quaternion(0.0f, -139.782f, 0.0f);
	rock01->GetTransform().Scale *= 0.15f;
	GameObject* rock02 = new GameObject;
	rock02->AddComponent(new MeshRenderer(rockMesh, rocksMaterial));
	rock02->GetTransform().Position = Vector3(-28.8458f, 0.0f, 0.1698152f);
	rock02->GetTransform().Rotation = Quaternion(0.0f, -70.933f, 0.0f);
	rock02->GetTransform().Scale *= 0.15f;
	GameObject* rock03 = new GameObject;
	rock03->AddComponent(new MeshRenderer(rockMesh, rocksMaterial));
	rock03->GetTransform().Position = Vector3(-13.44f, 0.0f, 18.28f);
	rock03->GetTransform().Rotation = Quaternion(0.0f, -13.0f, 0.0f);
	rock03->GetTransform().Scale *= 0.15f;
	GameObject* rock04 = new GameObject;
	rock04->AddComponent(new MeshRenderer(rockMesh, rocksMaterial));
	rock04->GetTransform().Position = Vector3(-19.38909f, 0.0f, -22.1042f);
	rock04->GetTransform().Rotation = Quaternion(0.0f, -130.933f, 0.0f);
	rock04->GetTransform().Scale *= 0.15f;
	GameObject* rock05 = new GameObject;
	rock05->AddComponent(new MeshRenderer(rockMesh, rocksMaterial));
	rock05->GetTransform().Position = Vector3(5.374193, 0.0f, -22.91925f);
	rock05->GetTransform().Rotation = Quaternion(0.0f, -30.933f, 0.0f);
	rock05->GetTransform().Scale *= 0.15f;

	flashLight = new SpotLight(Color(0xffbafbfc), 0.7f, 15.0f, 50.0f, 15.0f);

	mainScene = new Scene(mainCamera);
	mainScene->Add(rock01);
	mainScene->Add(rock02);
	mainScene->Add(rock03);
	mainScene->Add(rock04);
	mainScene->Add(rock05);
	mainScene->Add(alienStatue);
	mainScene->Add(gates);
	mainScene->Add(ground);
	mainScene->Add(floorCircular);
	mainScene->Add(sun);
	mainScene->Add(ambientLight);

	SetActiveScene(mainScene);

	//mainScene->Add(flashLight);
	uiLayer = new UILayer();
}

void Demo::Update()
{
	//fpsLabel->
	mainCamera->GetComponent<FpsCamera>()->Update(GetDeltaTime());
	//mainCamera->GetTransform().LookAt(alienStatue->GetTransform());
	//alienStatue->GetTransform().LookAt(mainCamera->GetTransform());

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
	PrimeEngineBase::Render();
	uiLayer->Render();
}