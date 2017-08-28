#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;

class FlappyBird : public PrimeEngineBase
{
private:
	GameLayer* playingLayer;
	Camera* mainCamera;
	GameObject *bird, *background, *groundPrefab, *pipeBottomPrefab, *pipeTopPrefab;
	std::vector<GameObject*> grounds, pipes;
	float birdRotation = 0.0f; //temp

private:
	void Destroy(GameObject* obj);

	void Gravity(GameObject& obj);
	void Jump(float height);
	void SpawnGround();
	void SpawnPipes();

public:
	~FlappyBird();

	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};