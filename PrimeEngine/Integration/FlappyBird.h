#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;

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
	bool isGameStarted_ = false;
	bool isGameOver_ = false;
    Font* arial;
	GameObject* scoreText;
	float angularMomentum = 0.0f;
	int score = 0;
	float goalX = 0.0f;
    float nextPipePosition = 0.0f;
	float birdRotation = 0.0f; //actually it's easier to have this; no need to constantly convert form quaternions to euler angles
	float groundPositionX = 0.0f;

private:
	void Destroy(GameObject* obj);
	void DestroyObjects(std::vector<GameObject*>& objects);
    bool DidBirdCollide();
    void RestartGame();
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