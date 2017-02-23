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

#if _DEBUG //need to add a more advanced loggin system to engine
#define LOG(x) cout<<x<<endl;
#else
#define LOG(x)
#endif // _DEBUG


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
	bool isStarting;
	float cellSize, gap;
	int placedCellCount = 0;
	Vector4 cellColor, linesColor, backGroundColor;
	SimpleRenderer2D renderer;
	Camera* mainCamera;
	Shader* myshader;
	Cell* cells[BOARD_SIZE * BOARD_SIZE];
	Vector3 cellPoints[BOARD_SIZE * BOARD_SIZE];
	Renderable2D *vLine1, *vLine2, *hLine1, *hLine2;
	NetworkEntity* party;

	TicTacToe(Vector4 _cellColor, const Vector4& _linesColor, const Vector4& _backGroundColor, NetworkEntity* _party, float _cellSize = 2.4f, float _gap = 0.1f) :
		PrimeEngine(true), cellColor(_cellColor), linesColor(_linesColor), backGroundColor(_backGroundColor), party(_party), cellSize(_cellSize), gap(_gap)
	{
		if (_party)
		{
			isStarting = party->isHost;
		}
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
		delete party;
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
			}
		}
		vLine1 = new Renderable2D(Vector3((gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), linesColor, *myshader);
		vLine2 = new Renderable2D(Vector3(-(gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), linesColor, *myshader);
		hLine1 = new Renderable2D(Vector3(0, (gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), linesColor, *myshader);
		hLine2 = new Renderable2D(Vector3(0, -(gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), linesColor, *myshader);
	}

	void SendCell(unsigned int i)
	{
		if (party)
		{
			std::ostringstream stream;
			stream << cellPoints[i] << ";" << cellColor;
			std::string str = stream.str();
			const char* chr = str.c_str();
			if (isStarting)
			{
				party->Send(chr);
			}
			isStarting = !isStarting;
		}
	}

	void ReceiveCell()
	{
		if (party && !isStarting)
		{
			char * pch;
			char* str = new char[1024];
			strcpy(str, party->Receive());
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
			LOG(position << " " << color);
			delete[] str;
			delete[] position;
			delete[] color;
			isStarting = !isStarting;
		}
	}

	void Place(Vector3 position)
	{
		int closesPoint = 0;
		for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		{
			if ((position - cellPoints[i]).SqrMagnitude() < (position - cellPoints[closesPoint]).SqrMagnitude())
			{
				closesPoint = i;
			}
		}
		if (placedCellCount >= BOARD_SIZE * BOARD_SIZE)
		{
			return;
		}
		if (position.x < cellPoints[closesPoint].x + cellSize / 2 && position.x > cellPoints[closesPoint].x - cellSize / 2 &&
			position.y < cellPoints[closesPoint].y + cellSize / 2 && position.y > cellPoints[closesPoint].y - cellSize / 2 &&
			cells[placedCellCount] && !cells[placedCellCount]->cellRenderer)
		{
			for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
			{
				if (cells[i] && cells[i]->cellRenderer && cells[i]->cellRenderer->GetPosition() == cellPoints[closesPoint])
				{
					return;
				}
			}
			cells[placedCellCount]->cellRenderer = new Renderable2D(cellPoints[closesPoint], Vector2(cellSize, cellSize), cellColor, *myshader);
			cells[placedCellCount]->isPlaced = true;
			placedCellCount++;
			SendCell(closesPoint);
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
				delete cells[i]->cellRenderer; // memory leak :(((
				cells[i]->cellRenderer = NULL; 
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
		ReceiveCell();
		mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
		if (Input::MouseButtonPressed(0))
		{
			Place(mainCamera->ScreenToWorldPoint(Input::GetMousePosition()));
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
		LOG(GetFPS() << "fps");
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
	NetworkEntity* entity = NULL;
	try
	{
		Vector4 lineColor(1, 1, 1, 1); //white
		Vector4 backGroundColor(0.858f, 0.815f, 0.364f, 1); //yellowish
		Vector4* cellColor = NULL;
		char option;
		cout << "Host or client? H/C ";
		cin >> option;
		if (option == 'h')
		{
			cout << "Host online " << endl;
			cout << "Waiting for client..." << endl;
			entity = new NetworkHost("27015");
			((NetworkHost*)entity)->Listen(); //need to make this cast safer
			cellColor = new Vector4(0.317f, 0.678f, 0.294f, 1); //greenish
		}
		else if(option == 'c')
		{
			cout << "Client online " << endl;
			entity = new NetworkClient("127.0.0.1", "27015");
			cellColor = new Vector4(0.850f, 0.368f, 0.427f, 1); //redish
		}
		else
		{
			cellColor = new Vector4(0.850f, 0.368f, 0.427f, 1); //redish
		}

		game = new TicTacToe(*cellColor, lineColor, backGroundColor, entity);
		delete cellColor;
		game->Play();
	}
	catch (const char* msg) //fix exception throwing, because this won't catch anything
	{
		delete game;
		cout << msg << endl;
		system("PAUSE");
	}
	return 0;
}