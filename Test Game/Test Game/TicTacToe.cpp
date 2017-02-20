#include <iostream>
#include <vector>

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

#define BOARD_SIZE 3

struct Cell
{
	bool isPlaced;
	Renderable2D* cellRenderer;

	Cell() :
		isPlaced(false), cellRenderer(NULL)
	{

	}

	~Cell()
	{
		if (cellRenderer)
		{
			delete cellRenderer;
		}
	}
};

class TicTacToe : public PrimeEngine::PrimeEngine
{
public:
	float cellSize, gap;
	int placedCellCount = 0;
	SimpleRenderer2D renderer;
	Camera* mainCamera;
	Shader* myshader;
	Cell* cells[BOARD_SIZE * BOARD_SIZE];
	Vector3 cellPoints[BOARD_SIZE * BOARD_SIZE];
	Renderable2D *vLine1, *vLine2, *hLine1, *hLine2;

	TicTacToe(float _cellSize = 2.4f, float _gap = 0.1f) : PrimeEngine(true), cellSize(_cellSize), gap(_gap)
	{

	}

	~TicTacToe()
	{
		for (int i = 0; i < 9; i++)
		{
			if (cells[i])
			{
				delete cells[i];
			}
		}
		delete vLine1;
		delete vLine2;
		delete hLine1;
		delete hLine2;
		delete mainCamera;
		delete myshader;
	}

	void CreateBoard()
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				cellPoints[i * BOARD_SIZE + j] = Vector3((i - 1) * (cellSize + gap), (j - 1) * (cellSize + gap), 0);
				cells[i * BOARD_SIZE + j] = new Cell();
				cells[i * BOARD_SIZE + j]->isPlaced = false;
				cells[i * BOARD_SIZE + j]->cellRenderer = NULL;
				//cout << cellPoints[i] << endl;
			}
		}
		//create cellpoints
		//cells[0] = new Renderable2D(Vector3(0, 0, 0), Vector2(cellSize, cellSize), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell1 = new Renderable2D(Vector3(-(size + offset), 0, 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell2 = new Renderable2D(Vector3((size + offset), 0, 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell3 = new Renderable2D(Vector3(0, (size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell4 = new Renderable2D(Vector3(-(size + offset), (size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell5 = new Renderable2D(Vector3((size + offset), (size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell6 = new Renderable2D(Vector3(0, -(size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell7 = new Renderable2D(Vector3(-(size + offset), -(size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		//cell8 = new Renderable2D(Vector3((size + offset), -(size + offset), 0), Vector2(size, size), Vector4(1, 0.5f, 0, 1), *myshader);
		vLine1 = new Renderable2D(Vector3((gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), Vector4(1, 1, 0, 1), *myshader);
		vLine2 = new Renderable2D(Vector3(-(gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), Vector4(1, 1, 0, 1), *myshader);
		hLine1 = new Renderable2D(Vector3(0, (gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), Vector4(1, 1, 0, 1), *myshader);
		hLine2 = new Renderable2D(Vector3(0, -(gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), Vector4(1, 1, 0, 1), *myshader);
	}

	void Place(Vector3 position)
	{
		//for (auto &pos : cellPoints) //trying out c++(11) foreach
		//{
		//	
		//}
		int closesPoint = 0;
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		{
			//cout << cellPoints[i] << endl;
			if ((position - cellPoints[i]).SqrMagnitude() < (position - cellPoints[closesPoint]).SqrMagnitude())
			{
				closesPoint = i;
			}
		}
		if (placedCellCount >= BOARD_SIZE * BOARD_SIZE)
		{
			return;
		}
		//cout << cellPoints[closesPoint] << endl;
		if (position.x < cellPoints[closesPoint].x + cellSize / 2 && position.x > cellPoints[closesPoint].x - cellSize / 2 &&
			position.y < cellPoints[closesPoint].y + cellSize / 2 && position.y > cellPoints[closesPoint].y - cellSize / 2 &&
			cells[placedCellCount] && !cells[placedCellCount]->cellRenderer)
		{
			for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
			{
				if (cells[i] && cells[i]->cellRenderer && cells[i]->cellRenderer->GetPosition() == cellPoints[closesPoint])
				{
					return;
					//closesPoint = i;
				}
			}
			//cout << "Placed!!!!!!!!!!" << endl;
			cells[placedCellCount]->cellRenderer = new Renderable2D(cellPoints[closesPoint], Vector2(cellSize, cellSize), Vector4(1, 0.5f, 0, 1), *myshader);
			cells[placedCellCount]->isPlaced = true;
			placedCellCount++;
		}
	}

	void Reset()
	{
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		{
			if (cells[i] && cells[i]->cellRenderer)
			{
				//cells[i] = NULL;
				//delete cells[i];
				//cells[i]->cellRenderer = NULL;
				delete cells[i]->cellRenderer;
				cells[i]->cellRenderer = NULL; //fucking memory leak :(((
				cells[i]->isPlaced = false;
				placedCellCount = 0;
			}
		}
	}

	void Awake() override
	{
		CreateWin("Tik Tac Toe", 1366, 768);
		//CreateWin("Tik Tac Toe", 800, 600);
		GetWindow()->SetColor(Vector4(0.3f, 0.6f, 1.0f, 1.0f));
		Matrix4x4 pr = Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);

		myshader = new Shader("standard.vert", "standard.frag");
		myshader->Enable();

		mainCamera = new Camera(*myshader, pr);
		Vector3 cameraPosition(Vector3(0, 0, 0.0f));
		mainCamera->SetPosition(cameraPosition);

		CreateBoard();
	}

	void Update() override
	{
		mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
		if (Input::MouseButtonPressed(0))
		{
			//place cell here
			Place(mainCamera->ScreenToWorldPoint(Input::GetMousePosition()));
			//cout << mainCamera->ScreenToWorldPoint(Input::GetMousePosition()) << endl;
		}
		if (Input::KeyPressed(' ')) //space
		{
			Reset();
		}
		if (Input::KeyPressed(256)) //esc
		{
			GetWindow()->Close();
		}
	}

	void Tick() override
	{
		//cout << GetFPS() << "fps" << endl;
	}

	void Render() override 
	{
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		{
			if (cells[i] && cells[i]->cellRenderer)
			{
				renderer.Submit(cells[i]->cellRenderer);
			}
		}
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