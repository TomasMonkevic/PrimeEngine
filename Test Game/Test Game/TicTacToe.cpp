#include <iostream>

#include <PrimeEngine.h>

#include <Core\Math.h>
#include <Input.h>

#include <Utilities\Time.h>

#include <Graphics\Window.h>
#include <Graphics\Shader.h>
#include <Graphics\Camera.h>
#include <Graphics\Renderable2D.h>
#include <Graphics\SimpleRenderer2D.h>

#include <Networking\NetworkClient.h>
#include <Networking\NetworkHost.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Graphics;
using namespace PrimeEngine::Input;
using namespace PrimeEngine::Networking;
//using namespace PrimeEngine;

using std::cout;
using std::cin;
using std::endl;

class TicTacToe : public PrimeEngine::PrimeEngine
{
public:
	SimpleRenderer2D renderer;
	Camera* mainCamera;
	Shader* myshader;
	Renderable2D *cell, *cell1, *cell2, *cell3, *cell4, *cell5, *cell6, *cell7, *cell8, *vLine1, *vLine2, *hLine1, *hLine2;

	TicTacToe() : PrimeEngine(true)
	{

	}

	~TicTacToe()
	{
		delete cell;
		delete cell1;
		delete cell2;
		delete cell3;
		delete cell4;
		delete cell5;
		delete cell6;
		delete cell7;
		delete cell8;
		delete vLine1;
		delete vLine2;
		delete hLine1;
		delete hLine2;
		delete mainCamera;
		delete myshader;
	}

	void Awake() override
	{
		CreateWin("Tik Tac Toe", 1366, 768);
		GetWindow()->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));

		//char option;
		//cout << "Host or client? H/C ";
		//cin >> option;
		//if (option == 'h')
		//{
		//	cout << "Host working" << endl;
		//	NetworkHost host("27015");
		//	host.Listen();
		//}
		//else
		//{
		//	cout << "Client msg: " << endl;
		//	NetworkClient client("127.0.0.1", "27015");
		//	client.Send("1234567890sfdsfdsf dsf sdf dsfdsf dsf dsfdsf dsfdsf ds"); //why is the mesage cut off?????
		//	cout << client.Receive() << endl;
		//}

		Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);

		myshader = new Shader("standard.vert", "standard.frag");
		myshader->Enable();

		mainCamera = new Camera(*myshader, pr);
		Vector3 cameraPosition(Vector3(0, 0, 0.0f));
		mainCamera->SetPosition(cameraPosition);

		float size = 2.4f, offset = 0.1;
		cell = new Renderable2D(Vector3(0, 0, 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell1 = new Renderable2D(Vector3(-(size + offset), 0, 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell2 = new Renderable2D(Vector3((size + offset), 0, 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell3 = new Renderable2D(Vector3(0, (size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell4 = new Renderable2D(Vector3(-(size + offset), (size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell5 = new Renderable2D(Vector3((size + offset), (size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell6 = new Renderable2D(Vector3(0, -(size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell7 = new Renderable2D(Vector3(-(size + offset), -(size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		cell8 = new Renderable2D(Vector3((size + offset), -(size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);

		vLine1 = new Renderable2D(Vector3((offset + size) / 2, 0, 0), Vector2(0.1f, 3 * size + 2 * offset), Vector4(1, 1, 0, 1), *myshader);
		vLine2 = new Renderable2D(Vector3(-(offset + size) / 2, 0, 0), Vector2(0.1f, 3 * size + 2 * offset), Vector4(1, 1, 0, 1), *myshader);
		hLine1 = new Renderable2D(Vector3(0, (offset + size) / 2, 0), Vector2(3 * size + 2 * offset, 0.1f), Vector4(1, 1, 0, 1), *myshader);
		hLine2 = new Renderable2D(Vector3(0, -(offset + size) / 2, 0), Vector2(3 * size + 2 * offset, 0.1f), Vector4(1, 1, 0, 1), *myshader);
	}

	void Update() override
	{
		mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
		if (Input::KeyPressed(256)) //esc
		{
			GetWindow()->Close();
		}
	}

	void Tick() override
	{
		cout << GetFPS() << "fps" << endl;
	}

	void Render() override 
	{
		renderer.Submit(cell);
		renderer.Submit(cell1);
		renderer.Submit(cell2);
		renderer.Submit(cell3);
		renderer.Submit(cell4);
		renderer.Submit(cell5);
		renderer.Submit(cell6);
		renderer.Submit(cell7);
		renderer.Submit(cell8);
		renderer.Submit(vLine1);
		renderer.Submit(vLine2);
		renderer.Submit(hLine1);
		renderer.Submit(hLine2);
		mainCamera->Render();
		renderer.Flush();
	}
};

int main()
{
	TicTacToe* game = NULL;
	try
	{
		//char option;
		//cout << "Host or client? H/C ";
		//cin >> option;
		//if (option == 'h')
		//{
		//	cout << "Host online " << endl;
		//	NetworkHost host("27015");
		//	host.Listen();
		//	cout << host.Receive() << endl;
		//	host.Send("This message was sent by the SERVER");
		//	host.DisconnectClient();
		//}
		//else
		//{
		//	cout << "Client online " << endl;
		//	NetworkClient client("127.0.0.1", "27015");
		//	client.Send("This message was sent by the CLIENT");
		//	cout << client.Receive() << endl;
		//}
		game = new TicTacToe;
		game->Play();
	}
	catch (const char* msg) //fix exception throwing, because this won't catch shit
	{
		delete game;
		cout << msg << endl;
		system("PAUSE");
	}
	return 0;
}