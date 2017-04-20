#include "Game.h"

void TestGame::Awake()
{
	//CreateWin("Tik Tac Toe", 1366, 768);
	CreateWin("Test Game", 800, 600);
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));

	Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	//Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

	gameShader = new Shader("Resources\\Shaders\\standard.vert", "Resources\\Shaders\\standard.frag");
	uiShader = new Shader("Resources\\Shaders\\standard.vert", "Resources\\Shaders\\standard.frag");

	mainCamera = new Camera(gameShader, pr);

	//Vector3 cameraPosition(Vector3(9, 4.5f, -6.0f)); //projection
	Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->SetPosition(cameraPosition);

	Sprite* backGround = new Sprite(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1));
	texture = new Texture("Resources\\Textures\\texture.png");
	//texture2 = new Texture("Resources\\Textures\\textur2.png");
	//texture3 = new Texture("Resources\\Textures\\1.jpg");
	//Texture* texture4 = new Texture("Resources\\Textures\\bc.png"); //openGL doesn't like this texture
	sprite1 = new Sprite(Vector3(0, -0.5f, 0.1f), Vector2(1, 1), texture, Vector4(0,0,1,1.0f));
	Sprite* sprite2 = new Sprite(Vector3(5, -0.5f, 0.1f), Vector2(1, 1), NULL);
	Sprite* sprite3 = new Sprite(Vector3(0, -0.5f, 0.1f), Vector2(3, 1), texture);

	gameLayer = new GameLayer(mainCamera);
	gameLayer->Submit(backGround);
	gameLayer->Submit(sprite3);
	gameLayer->Submit(sprite2);
	gameLayer->Submit(sprite1);

	buttonContainer = new Group(Vector3(-6, 0, 0), Vector2(10, 10));
	button = new Group(Vector3(0, 1.5f, 0), Vector2(10, 10));
	Sprite* uiEl = new Sprite(Vector3(0, 0, 0), Vector2(4, 1), Vector4(1.0f, 0.0f, 0.0f, 1));
	buttonContainer->Add(button);
	buttonContainer->Add(uiEl);
	button->Add(new Sprite(Vector3(0, 0.0f, 0), Vector2(4, 1), Vector4(1.0f, 0.0f, 0.0f, 1)));
	button->Add(new Sprite(Vector3(0, 0.0f, 0), Vector2(3, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1)));
	uiLayer = new FakeUILayer(uiShader);
	uiLayer->Submit(buttonContainer);
}

void TestGame::Update()
{
	//Change light position
	//Vector3 opa = mainCamera->ScreenToWorldPoint(Input::GetMousePosition());
	//Vector3 opa2 = uiLayer->camera->ScreenToWorldPoint(Input::GetMousePosition());
	//gameShader->SetUniform("lightPosition", Vector2(opa.x, opa.y));
	//uiShader->SetUniform("lightPosition", Vector2(opa2.x, opa2.y));
	//Rotate ui
	buttonContainer->Rotate(GetDeltaTime(), Vector3::forward);
	button->Rotate(GetDeltaTime(), Vector3::left);

	sprite1->Rotate(GetDeltaTime(), Vector3::forward);
	if (Input::KeyPressed(256)) //esc
	{
		GetWindow()->Close();
	}
}

void TestGame::Tick()
{
	LOG(GetFPS() << "fps");
	//cout << GetFPS() << "fps" << endl;
}

void TestGame::Render()
{
	gameLayer->Render();
	uiLayer->Render();
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
	mainCamera->Render();
}