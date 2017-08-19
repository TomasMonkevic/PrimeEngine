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

	Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
	//Matrix4x4 pr = Matrix4x4::Perspective(45.0f, 16.0f / 9.0f, -1.5f, 1.5f);

	mainCamera = new Camera(ShaderManagerI->CreateShader("gameShader", Shader::default), pr);

	//Vector3 cameraPosition(Vector3(9, 4.5f, -6.0f)); //projection
	Vector3 cameraPosition(Vector3(0, 0, 0.0f)); //ortho
	mainCamera->SetPosition(cameraPosition);

	//Sprite* backGround = new Sprite(Vector3(5, 4.5f, 0.1f), Vector2(100, 100), Color(1, 0.5f, 0, 1.0f));
	//texture3 = new Texture("Resources\\Textures\\1.jpg");
	//Texture* texture4 = new Texture("Resources\\Textures\\bc.png"); //openGL doesn't like this texture
	//sprite1 = new Sprite(Vector3(0, -0.5f, 0.1f), Vector2(5, 5), texture, Color(0.55f,0.55f,1,1.0f));
	//Sprite* sprite2 = new Sprite(Vector3(5, -0.5f, 0.1f), Vector2(1, 1), NULL);
	//Sprite* sprite3 = new Sprite(Vector3(0, -0.5f, 0.1f), Vector2(2, 2), texture2);
	//PRIME_WARNING(sprite2->GetPosition());

	gameLayer = new GameLayer(mainCamera);
	uiLayer = new UILayer(ShaderManagerI->CreateShader("uiShader", Shader::default));
	//gameLayer->Submit(backGround);
	//gameLayer->Submit(sprite3);
	//gameLayer->Submit(sprite2);
	//gameLayer->Submit(sprite1);

	buttonContainer = new GameObject(Vector3(-6, 0, 0));
	buttonContainer->AddComponent(new Sprite(Vector2(4, 1), Color(1.0f, 0.0f, 0.0f, 0.5f)));

	button = new GameObject(Vector3(0, 1.5f, 0));
	button->AddComponent(new Sprite(Vector2(4, 1), Color(1.0f, 0.0f, 0.0f, 0.5f)));
	GameObject* eil = new GameObject();
	eil->AddComponent(new Sprite(Vector2(3, 0.5f), Color(0.0f, 0.0f, 1.0f)));
	button->Add(eil);

	buttonContainer->Add(button);

	myFont = new Font("Resources\\arial.ttf", Color(1.0f, 1.0f, 1.0f), 64);
	std::string wtf = "HE HE HE HE";
	//fpsLabel = new GameObject(Vector2(-8.0f, -4.5f));
	//fpsLabel->AddComponent(new Label(wtf, *myFont));
	//uiLayer->Submit(fpsLabel);
	//gameLayer->Submit(fpsLabel);
	testText = new UI::Text(wtf, *myFont);
	//uiLayer->Submit(testText);

	//uiLayer->Submit(buttonContainer);
	gameLayer->Submit(buttonContainer);
	player = new GameObject();
	player->AddComponent(new Sprite (Vector2(2, 2), "Resources\\Textures\\pepe.png"));
	gameLayer->Submit(player);
	//Transform* trans = player.GetComponent<Transform>();
	PRIME_WARNING(player->GetTransform().GetPosition(), "\n");
	//player.GetTransform().SetPosition(Math::Vector3::one);
	//player.GetTransform().
	//PRIME_WARNING(player.GetTransform().GetPosition(), "\n");
}

void TestGame::Update()
{
	//Change light position
	//Vector3 opa = mainCamera->ScreenToWorldPoint(Input::GetMousePosition());
	//Vector3 opa2 = uiLayer->camera->ScreenToWorldPoint(Input::GetMousePosition());
	//gameShader->SetUniform("lightPosition", Vector2(opa.x, opa.y));
	//uiShader->SetUniform("lightPosition", Vector2(opa2.x, opa2.y));
	//Rotate ui
	//buttonContainer->GetTransform().Rotate(GetDeltaTime(), Vector3::forward());
	//button->GetTransform().Rotate(GetDeltaTime(), Vector3::left());
	//sprite1->Rotate(GetDeltaTime(), Vector3::forward);
	if (InputPC::GetKey('W')) //esc
	{
		player->GetTransform().SetPosition(player->GetTransform().GetPosition() + Vector3::up() * GetDeltaTime() * speed);
	}
	else if (InputPC::GetKey('S')) //esc
	{
		player->GetTransform().SetPosition(player->GetTransform().GetPosition() + Vector3::down() * GetDeltaTime() * speed);
	}
	if (InputPC::GetKey('A')) //esc
	{
		player->GetTransform().SetPosition(player->GetTransform().GetPosition() + Vector3::left() * GetDeltaTime() * speed);
	}
	else if (InputPC::GetKey('D')) //esc
	{
		player->GetTransform().SetPosition(player->GetTransform().GetPosition() + Vector3::right() * GetDeltaTime() * speed);
	}
	mainCamera->SetPosition(player->GetTransform().GetPosition());
	if (InputPC::GetKeyDown(256)) //esc
	{
		GetWindow()->Close();
	}
}

void TestGame::Tick()
{
	PRIME_INFO(GetFPS(), " fps \n");
	//Label* label = static_cast<Label*>(fpsLabel->GetComponent<Renderable>());
	//label->text = std::to_string(GetFPS()) + " FPS";
	srand(time(NULL));
	float random = (float)(rand() % 100) / 100.0f;
	float random1 = (float)(rand() % 100) / 100.0f;
	float random2 = (float)(rand() % 100) / 100.0f;
	//PRIME_WARNING(random, " ", random1, " ", random2, "\n");
	//label->font->color = Color(random, random1, random2);
	//PRIME_INFO(myFont->color, "\n");
}

void TestGame::Render()
{
	mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back());
	mainCamera->Render();
	gameLayer->Render();
	uiLayer->Render();
}