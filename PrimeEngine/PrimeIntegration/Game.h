#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;
using namespace Networking;

using std::cout;
using std::cin;
using std::endl;

struct TempVertexData
{
	Vector3 position;
	unsigned color32;
};

class TestGame : public PrimeEngineBase
{
private:
	GameLayer* gameLayer;
	Camera* mainCamera;
	GameObject *player;
	IndexBuffer* _ibo;
	VertexArray* _vao;
	VertexBuffer* _vbo;

public:
	~TestGame() 
	{
		delete gameLayer;
		delete player;
		delete _vbo;
		delete _vao;
		delete _ibo;
	}
	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};