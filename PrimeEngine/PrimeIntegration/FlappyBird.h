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
	GameObject *bird, *background, *groundPrefab;
	std::vector<GameObject*> grounds;
	float birdRotation = 0.0f; //temp

private:
	void Gravity(GameObject& obj);
	void Jump(float height);
	void SpawnGround();

public:
	~FlappyBird();

	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};