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

private:
	void Gravity(GameObject& obj);

public:
	~FlappyBrid();

	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};