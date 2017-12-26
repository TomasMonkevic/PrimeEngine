#pragma once

#include <PrimeEngine.h>
#include <DllExport.h>

using namespace PrimeEngine::Math;
using namespace PrimeEngine::Input;

namespace PrimeEngine {

	class PRIMEENGINEAPI FpsCamera : public Behaviour
	{
	private:
		float cameraSpeed = 10.0f;
		Vector2 mouseSensitivity = Vector2(0.015f, 0.015f);

	public:
		FpsCamera();

		void Update(float deltaTime) override;
		
		Component* Copy() override;
	};
}