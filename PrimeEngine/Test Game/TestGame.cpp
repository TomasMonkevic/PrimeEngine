#include "TestGame.h"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{
	delete uiLayer;
	delete gameLayer;
	delete sprite1;
	delete button;
	delete buttonContainer;
}

void TestGame::Awake()
{
	//CreateWin("Tik Tac Toe", 1366, 768);
	CreateWin("Test Game", 800, 600);
	GetWindow()->EnableVSync(true);
	GetWindow()->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));

	Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	//Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

	gameShader = new Shader("standard.vert", "standard.frag");
	//gameShader->Enable();
	//uiShader = new Shader("standard.vert", "standard.frag");

	mainCamera = new Camera(gameShader, pr);

	//Vector3 cameraPosition(Vector3(9, 4.5f, -6.0f)); //projection
	Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->SetPosition(cameraPosition);

	//Sprite* backGround = new Sprite(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Vector4(1, 0.5f, 0, 1));
	sprite1 = new Sprite(Vector3(5, 1.5f, 0.1f), Vector2(1, 2), Vector4(1, 1, 0, 1));

	gameLayer = new GameLayer(mainCamera);
	//gameLayer->Submit(backGround);
	gameLayer->Submit(sprite1);

	texture = new Texture("texture.png");
	texture->Bind();
	gameShader->SetUniform("outTexture", 0);
	//buttonContainer = new Group(Vector3(-6, 0, 0), Vector2(10, 10));
	//button = new Group(Vector3(0, 1.5f, 0), Vector2(10, 10));
	//Sprite* uiEl = new Sprite(Vector3(0, 0, 0), Vector2(4, 1), Vector4(1.0f, 0.0f, 0.0f, 1));
	//buttonContainer->Add(button);
	//buttonContainer->Add(uiEl);
	//button->Add(new Sprite(Vector3(0, 0.0f, 0), Vector2(4, 1), Vector4(1.0f, 0.0f, 0.0f, 1)));
	//button->Add(new Sprite(Vector3(0, 0.0f, 0), Vector2(3, 0.5f), Vector4(0.0f, 0.0f, 1.0f, 1)));
	//uiLayer = new FakeUILayer(uiShader);
	//uiLayer->Submit(buttonContainer);
}

void TestGame::Update()
{
	//Change light position
	Vector3 opa = mainCamera->ScreenToWorldPoint(Input::GetMousePosition());
	//Vector3 opa2 = uiLayer->camera->ScreenToWorldPoint(Input::GetMousePosition());
	gameShader->SetUniform("lightPosition", Vector2(opa.x, opa.y));
	//uiShader->SetUniform("lightPosition", Vector2(opa2.x, opa2.y));
	//Rotate ui
	//buttonContainer->Rotate(GetDeltaTime(), Vector3::forward);
	//button->Rotate(GetDeltaTime(), Vector3::forward);

	//sprite1->Rotate(GetDeltaTime() * speed, Vector3::forward);
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
	//uiLayer->Render();
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
	//mainCamera->Render();
}