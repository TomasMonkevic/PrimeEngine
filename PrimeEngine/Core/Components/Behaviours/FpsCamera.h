#pragma once

#include <PrimeEngine.h> //TODO should only include necessary includes
#include <DllExport.h>

namespace PrimeEngine {

	class PRIMEENGINEAPI FpsCamera : public Behaviour
	{
	private:
		float _cameraSpeed;
		Math::Vector2 _mouseSensitivity;

		Math::Vector2 _positionTouchStartPosition;
		Math::Vector2 _rotationTouchStartPosition;

	public:
		FpsCamera(float cameraSpeed, const Math::Vector2& mouseSensitivity);

		void Update(float deltaTime) override;
		
		Component* Copy() override;

	private:
		bool IsLeftSideTouch(Math::Vector2 position);
	};
}