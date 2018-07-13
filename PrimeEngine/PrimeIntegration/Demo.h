#pragma once

#include <PrimeEngine.h>

using namespace PrimeEngine;
using namespace Math;
using namespace Graphics;
using namespace Input;
using namespace Networking;
using namespace PrimeEngine::Graphics::Lights;

using std::cout;
using std::cin;
using std::endl;

class Demo : public PrimeEngineBase
{
private:
	Scene * mainScene;
	Camera* mainCamera;
	DirectionalLight* sun;

	SpotLight* flashLight;

public:
	~Demo()
	{
		delete mainScene;
	}
	void Awake() override;
	void Update() override;
	void Tick() override;
	void Render() override;
};
