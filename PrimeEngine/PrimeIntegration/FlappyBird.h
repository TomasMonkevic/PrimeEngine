#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;
using namespace UI;

class FlappyBird : public PrimeEngineBase
{
private:
	//think about changing to stack
	GameLayer* playingLayer;
	UILayer* uiLayer;
	Camera* mainCamera;
	GameObject *bird, *background, *groundPrefab, *pipeBottomPrefab, *pipeTopPrefab;
	std::vector<GameObject*> grounds, pipes;
	Vector2 birdVelocity = Vector2::zero();
	Font arial = Font("Resources\\arial.ttf", Color(1.0f, 1.0f, 1.0f), 64);
	Text* score;
	float angularMomentum = 0.0f;
	float birdRotation = 0.0f; //actually it's easier to have this; no need to constantly convert form quaternions to euler angles

private:
	void Destroy(GameObject* obj);

	void Gravity(GameObject& obj);
	//void Jump(float height);
	void SpawnGround();
	void SpawnPipes();

public:
	~FlappyBird();

	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};