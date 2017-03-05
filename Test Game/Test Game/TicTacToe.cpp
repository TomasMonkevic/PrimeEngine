#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>

#include <Networking\NetworkClient.h>
#include <Networking\NetworkHost.h>

#include <PrimeEngine.h>


#include <Utilities\Time.h>

#include <Core\Math.h>
#include <Input.h>

#include <Graphics\Window.h>
#include <Graphics\Shader.h>
#include <Graphics\Camera.h>
#include <Graphics\Renderable2D.h>
#include <Graphics\SimpleRenderer2D.h>

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
	bool isEnemy;
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
	enum GameOver { loser, winner, tie };

	GameOver gameEnd;
	bool isStarting, isGameOver, isPlacedByEnemy;
	float cellSize, gap;
	int placedCellCount = 0;
	Vector4 enemyColor, cellColor, linesColor, backGroundColor;
	SimpleRenderer2D renderer;
	Camera* mainCamera;
	Shader* myshader;
	Cell* cells[BOARD_SIZE * BOARD_SIZE];
	Vector3 cellPoints[BOARD_SIZE * BOARD_SIZE], enemyPos;
	Renderable2D *vLine1, *vLine2, *hLine1, *hLine2;
	NetworkEntity* party;

	TicTacToe(Vector4 _cellColor, const Vector4& _linesColor, const Vector4& _backGroundColor, NetworkEntity* _party, float _cellSize = 2.4f, float _gap = 0.1f) :
		PrimeEngine(true), cellColor(_cellColor), linesColor(_linesColor), backGroundColor(_backGroundColor), party(_party), cellSize(_cellSize), gap(_gap)
	{
		if (_party)
		{
			isStarting = party->isHost;
		}
		else
		{
			isStarting = true;
		}
		isGameOver = false;
		isPlacedByEnemy = false;
		gameEnd = loser;
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
				cellPoints[i * BOARD_SIZE + j] = Vector3((j - 1) * (cellSize + gap), (i - 1) * (cellSize + gap), 0);
				LOG(cellPoints[i * BOARD_SIZE + j]);
				cells[i * BOARD_SIZE + j] = new Cell();
				cells[i * BOARD_SIZE + j]->isPlaced = false;
				cells[i * BOARD_SIZE + j]->isEnemy = true;
				cells[i * BOARD_SIZE + j]->cellRenderer = NULL;
			}
		}
		vLine1 = new Renderable2D(Vector3((gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), linesColor, *myshader);
		vLine2 = new Renderable2D(Vector3(-(gap + cellSize) / 2, 0, 0), Vector2(0.1f, 3 * cellSize + 2 * gap), linesColor, *myshader);
		hLine1 = new Renderable2D(Vector3(0, (gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), linesColor, *myshader);
		hLine2 = new Renderable2D(Vector3(0, -(gap + cellSize) / 2, 0), Vector2(3 * cellSize + 2 * gap, 0.1f), linesColor, *myshader);
	}

	void SendPackage(bool isReset, unsigned int i = 0) //think about this function
	{
		if (party)
		{
			std::ostringstream stream;
			stream << isReset << ";" << gameEnd << ";" << cellPoints[i] << ";" << cellColor; //could be optimized
			std::string str = stream.str();
			const char* chr = str.c_str();
			if (isStarting)
			{
				party->Send(chr);
			}
			isStarting = !isStarting;
		}
	}

	Cell* GetCellByPosition(const Vector3& position)
	{
		int i = 0;
		while (i < BOARD_SIZE * BOARD_SIZE)
		{
			if (cells[i] && cells[i]->cellRenderer && cells[i]->cellRenderer->GetPosition() == position)
			{
				return cells[i];
			}
			i++;
		}
		return NULL;
	}

	bool IsWinner(int index) //O(BOARD_SIZE) - linear
	{
		int x = index % BOARD_SIZE;
		int y = index / BOARD_SIZE;
		Cell* foundCell;
		bool isWinner = false;
		for (int i = 0; i < BOARD_SIZE; i++) //vertical check
		{
			foundCell = GetCellByPosition(cellPoints[i * BOARD_SIZE + x]);
			if (!foundCell || foundCell->isEnemy)
			{
				goto checkHorizontal;
			}
		}
		return true;
		checkHorizontal:
		for (int i = 0; i < BOARD_SIZE; i++) //horizontal check
		{
			foundCell = GetCellByPosition(cellPoints[y * BOARD_SIZE + i]);
			if (!foundCell || foundCell->isEnemy)
			{
				goto checkDiagonal1;
			}
		}
		return true;
		checkDiagonal1:
		for (int i = 0; i < BOARD_SIZE; i++) //diagonal(bottom-top) check
		{
			foundCell = GetCellByPosition(cellPoints[i * BOARD_SIZE + i]);
			if (!foundCell || foundCell->isEnemy)
			{
				goto checkDiagonal2;
			}
		}
		return true;
		checkDiagonal2:
		for (int i = 0; i < BOARD_SIZE; i++) //diagonal(top-bottom) check
		{
			foundCell = GetCellByPosition(cellPoints[i * BOARD_SIZE + (BOARD_SIZE - 1 - i)]);
			if (!foundCell || foundCell->isEnemy)
			{
				goto noWin;
			}
		}
		return true;
		noWin:
		return false;
	}

	void GameOver()
	{
		if (gameEnd == winner)
		{
#if _WIN32
			MessageBox(NULL, "You win!", "Game Over", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
#else
			cout << "You win!" << endl;
#endif
		}
		else if (gameEnd == tie)
		{
#if _WIN32
			MessageBox(NULL, "It's a tie!", "Game Over", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
#else
			cout << "It's a tie!" << endl;
#endif
		}
		else
		{
#if _WIN32
			MessageBox(NULL, "You lose!", "Game Over", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
#else
			cout << "You lose!" << endl;
#endif
		}
		Reset();
	}

	void ReceivePackage()
	{
		while (true)
		{
			if (party && !isStarting)
			{
				char* buffer = new char[1024];
				strcpy(buffer, party->Receive());
				LOG(buffer);
				char* position;
				char* color;
				char* isReset;
				char* isWin;
				isReset = strtok(buffer, ";");
				if (!isReset) //implement better disconnection
				{
					party->Disconnect();
					return;
				}
				if (*isReset == '1')
				{
					Reset();
				}
				else
				{
					isWin = strtok(NULL, ";");
					if (*isWin == '1')
					{
						gameEnd = loser;
						isGameOver = true;
					}
					else if (*isWin == '2')
					{
						gameEnd = tie;
						isGameOver = true;
					}
					//else
					//{
					position = strtok(NULL, ";");
					color = strtok(NULL, ";");
					isPlacedByEnemy = true;
					enemyPos = Vector3::Create(position);
					enemyColor = Vector4::Create(color);
					//}
				}
				delete[] buffer;
				isStarting = !isStarting;
			}
		}
	}

	void PlaceCell(const Vector3& position, const Vector4& color, bool isEnemy)
	{
		cells[placedCellCount]->cellRenderer = new Renderable2D(position, Vector2(cellSize, cellSize), color, *myshader);
		cells[placedCellCount]->isPlaced = true;
		cells[placedCellCount]->isEnemy = isEnemy;
		placedCellCount++;
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
			if (GetCellByPosition(cellPoints[closesPoint]))
			{
				return;
			}
			PlaceCell(cellPoints[closesPoint], cellColor, false);
			bool isWinner = IsWinner(closesPoint);
			if (isWinner)
			{
				gameEnd = winner;
				isGameOver = true;
			}
			if (!isWinner && placedCellCount == BOARD_SIZE * BOARD_SIZE)
			{
				gameEnd = tie;
				isGameOver = true;
			}
			SendPackage(false, closesPoint);
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
				cells[i]->isEnemy = true;
				cells[i]->isPlaced = false;
				placedCellCount = 0;
				isGameOver = false;
				gameEnd = loser;
			}
		}
	}

	void Awake() override
	{
		//CreateWin("Tik Tac Toe", 1366, 768);
		CreateWin("Tik Tac Toe", 800, 600);
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
		if (isPlacedByEnemy)
		{
			PlaceCell(enemyPos, enemyColor, true);
			LOG(enemyPos << " " << enemyColor);
			isPlacedByEnemy = false;
		}
		if (isGameOver)
		{
			Draw();
			GetWindow()->Update();
			GameOver();
		}
		mainCamera->LookAt(mainCamera->GetPosition() + Vector3::back);
		if (Input::MouseButtonPressed(0) && !isGameOver && isStarting)
		{
			Place(mainCamera->ScreenToWorldPoint(Input::GetMousePosition()));
		}
		if (Input::KeyPressed(256)) //esc
		{
			party->Disconnect();
			GetWindow()->Close();
		}
	}

	void Tick() override
	{
		LOG(GetFPS() << "fps");
	}

	inline void Draw()
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

	void Render() override 
	{
		Draw();
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
		std::string port;
		cout << "Host or client? H/C ";
		cin >> option;
		bool start = false;
		if (option == 'h' || option == 'H')
		{
			cout << "Host online " << endl;
			cout << "Enter server's port: ";
			cin >> port;
			cout << "Waiting for client..." << endl;
#if _DEBUG
			entity = new NetworkHost("2075");
#else
			entity = new NetworkHost(port.c_str());
#endif
			((NetworkHost*)entity)->Listen(); //need to make this cast safer
			cellColor = new Vector4(0.317f, 0.678f, 0.294f, 1); //greenish
		}
		else if(option == 'c' || option == 'C')
		{
			std::string ip;
			cout << "Client online " << endl;
			cout << "Enter server's IP address: ";
			cin >> ip;
			cout << "Enter server's port: ";
			cin >> port;
#if _DEBUG
			entity = new NetworkClient("127.0.0.1", "2075"); //"127.0.0.1" - localhost
#else
			entity = new NetworkClient(ip.c_str(), port.c_str()); 
#endif
			//----------------- Multiclient stuff ------------
			//entity->Receive();
			//LOG(entity->Receive());
			cout << "Waiting for partner..." << endl;
			if (*(entity->Receive()) == '1')
			{
				start = true;
				cellColor = new Vector4(0.317f, 0.678f, 0.294f, 1); //greenish
			}
			else
			{
				cellColor = new Vector4(0.850f, 0.368f, 0.427f, 1); //redish
			}
		}
		else
		{
			cellColor = new Vector4(0.850f, 0.368f, 0.427f, 1); //redish
		}

		game = new TicTacToe(*cellColor, lineColor, backGroundColor, entity);
		game->isStarting = start;
		std::thread(&TicTacToe::ReceivePackage, std::ref(game)).detach();
		LOG(*cellColor);
		delete cellColor;
		game->Play();
	}
	catch (const char* msg) //fix exception throwing, because this won't catch anything
	{
		cout << msg << endl;
		delete game;
		system("PAUSE");
	}
	return 0;
}