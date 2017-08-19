#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;

class FlappyBrid : public PrimeEngineBase
{
private:
	GameLayer* playingLayer;
	Camera* mainCamera;
	GameObject *bird, *background, *ground;
	float birdRotation = 0.0f; //temp

private:
	void Gravity(GameObject& obj);
	void Jump(float height);

public:
	~FlappyBrid();

	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};