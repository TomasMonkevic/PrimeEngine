#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

NetworkHost* host = NULL; //making global for now
NetworkClient* client = NULL;

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
	bool isHost, isStarting;
	float cellSize, gap;
	int placedCellCount = 0;
	Vector4 cellColor, linesColor, backGroundColor;
	SimpleRenderer2D renderer;
	Camera* mainCamera;
	Shader* myshader;
	Cell* cells[BOARD_SIZE * BOARD_SIZE];
	Vector3 cellPoints[BOARD_SIZE * BOARD_SIZE];
	Renderable2D *vLine1, *vLine2, *hLine1, *hLine2;

	TicTacToe(Vector4 _cellColor, const Vector4& _linesColor, const Vector4& _backGroundColor, bool _isHost, bool _isStarting, float _cellSize = 2.4f, float _gap = 0.1f) :
		PrimeEngine(true), cellColor(_cellColor), linesColor(_linesColor), backGroundColor(_backGroundColor), isHost(_isHost), isStarting(_isStarting), cellSize(_cellSize), gap(_gap)
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
		vLine1 = new Renderable2D(Vector3((gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), linesColor, *myshader);
		vLine2 = new Renderable2D(Vector3(-(gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), linesColor, *myshader);
		hLine1 = new Renderable2D(Vector3(0, (gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), linesColor, *myshader);
		hLine2 = new Renderable2D(Vector3(0, -(gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), linesColor, *myshader);
	}

	void Place(Vector3 position)
	{
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
			cells[placedCellCount]->cellRenderer = new Renderable2D(cellPoints[closesPoint], Vector2(cellSize, cellSize), cellColor, *myshader);
			cells[placedCellCount]->isPlaced = true;
			placedCellCount++;
			std::ostringstream stream;
			stream << cellPoints[closesPoint] << ";" << cellColor;
			std::string str = stream.str();
			const char* chr = str.c_str();
			if (isHost) //implement interface for networking
			{

				if (isStarting)
				{
					host->Send(chr);
				}
			}
			else
			{
				if (isStarting)
				{
					client->Send(chr);
				}
			}
			isStarting = !isStarting;
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
		GetWindow()->SetColor(backGroundColor);
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
		if (isHost) //implement interface for networking
		{
			if (!isStarting)
			{
				char * pch;
				char* str = new char[1024];
				strcpy(str, host->Receive());
				char* position = new char[1024];
				char* color = new char[1024];
				pch = strtok(str, ";");
				strcpy(position, pch);
				pch = strtok(NULL, ";");
				//pch = strtok(str, ";");
				strcpy(color, pch);
				cells[placedCellCount]->cellRenderer = new Renderable2D(Vector3::Create(position), Vector2(cellSize, cellSize), Vector4::Create(color), *myshader);
				cells[placedCellCount]->isPlaced = true;
				placedCellCount++;
				cout << position << " " << color << endl;
				delete[] str;
				delete[] position;
				delete[] color;
				//cout << host->Receive() << endl;
				isStarting = !isStarting;
			}
		}
		else
		{
			if (!isStarting)
			{
				char * pch;
				char* str = new char[1024];
				strcpy(str, client->Receive());
				pch = strtok(str, ";");
				char* position = new char[1024];
				strcpy(position, pch);
				pch = strtok(NULL, ";");
				//pch = strtok(str, ";");
				char* color = new char[1024];
				strcpy(color, pch);
				cells[placedCellCount]->cellRenderer = new Renderable2D(Vector3::Create(position), Vector2(cellSize, cellSize), Vector4::Create(color), *myshader);
				cells[placedCellCount]->isPlaced = true;
				placedCellCount++;
				cout << position << " " << color << endl;
				delete[] str;
				delete[] position;
				delete[] color;
				//cout << client->Receive() << endl;
				isStarting = !isStarting;
			}
		}
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
		cout << GetFPS() << "fps" << endl;
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
		//Vector3 rez = Vector3::Create("(-1.01, 0, 1)");
		//cout<<rez.Magnitude()<<endl;
		Vector4 lineColor(1, 1, 1, 1); //white
		Vector4 backGroundColor(0.858f, 0.815f, 0.364f, 1); //yellowish
		Vector4* cellColor = NULL;
		char option;
		bool isHost;
		cout << "Host or client? H/C ";
		cin >> option;
		if (option == 'h')
		{
			cout << "Host online " << endl;
			host = new NetworkHost("27015");
			host->Listen();
			//cout << host.Receive() << endl;
			//host.Send("This message was sent by the SERVER");
			//host.DisconnectClient();
			isHost = true;
			cellColor = new Vector4(0.317f, 0.678f, 0.294f, 1); //greenish
		}
		else
		{
			cout << "Client online " << endl;
			client = new NetworkClient("127.0.0.1", "27015");
			//client = new NetworkClient("78.60.19.86", "27015");
			//client.Send("This message was sent by the CLIENT");
			//cout << client.Receive() << endl;
			isHost = false;
			cellColor = new Vector4(0.850f, 0.368f, 0.427f, 1); //redish
		}

		game = new TicTacToe(*cellColor, lineColor, backGroundColor, isHost, isHost);
		delete cellColor;
		game->Play();
		delete host;
		delete client;
	}
	catch (const char* msg) //fix exception throwing, because this won't catch shit
	{
		delete game;
		cout << msg << endl;
		system("PAUSE");
	}
	return 0;
}