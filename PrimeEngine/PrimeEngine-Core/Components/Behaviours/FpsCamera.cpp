#include "FpsCamera.h"

using namespace PrimeEngine::Math;
#ifndef PE_ANDROID
using namespace PrimeEngine::Input;
#endif

namespace PrimeEngine {

	FpsCamera::FpsCamera(float cameraSpeed, const Vector2& mouseSensitivity)
		: _cameraSpeed(cameraSpeed), _mouseSensitivity(mouseSensitivity)
	{
		AddType<FpsCamera>();
	}

	void FpsCamera::Update(float deltaTime)
	{
		#ifndef PE_ANDROID
		if (InputPC::GetKey('A'))
		{
			GetGameObject()->GetTransform().Position -= GetGameObject()->GetTransform().Right() * _cameraSpeed * deltaTime;
		}
		else if (InputPC::GetKey('D'))
		{
			GetGameObject()->GetTransform().Position += GetGameObject()->GetTransform().Right() * _cameraSpeed * deltaTime;
		}
		if (InputPC::GetKey('W'))
		{
			GetGameObject()->GetTransform().Position += GetGameObject()->GetTransform().Forward() * _cameraSpeed * deltaTime;
		}
		else if (InputPC::GetKey('S'))
		{
			GetGameObject()->GetTransform().Position -= GetGameObject()->GetTransform().Forward() * _cameraSpeed * deltaTime;
		}
		if (InputPC::GetKey('Q'))
		{
			GetGameObject()->GetTransform().Position += Vector3::up() * _cameraSpeed * deltaTime;
		}
		else if (InputPC::GetKey('E'))
		{
			GetGameObject()->GetTransform().Position -= Vector3::up() * _cameraSpeed * deltaTime;
		}
		static Vector2 pervMousePos;
		Vector2 deltaMouse = InputPC::GetMousePosition() - pervMousePos;

		//TODO magic happens here ///
		// Yaw happens "over" the current rotation, in global coordinates.
		Quaternion yaw = Quaternion::Rotation(deltaMouse.x * _mouseSensitivity.x, Vector3::up());
		GetGameObject()->GetTransform().Rotation = yaw * GetGameObject()->GetTransform().Rotation; // yaw on the left.
		// Pitch happens "under" the current rotation, in local coordinates.
		Quaternion pitch = Quaternion::Rotation(deltaMouse.y * _mouseSensitivity.y, Vector3::right());
		GetGameObject()->GetTransform().Rotate(pitch); // pitch on the right.
		//////////////////////////////////////////

		//PRIME_INFO(mainCamera->GetTransform().Rotation, '\n');
		pervMousePos = InputPC::GetMousePosition();
        #else
        std::vector<Input::Touch> touches = Input::InputPC::GetTouches();
        if(touches.size() == 2) {
            GetGameObject()->GetTransform().Position += GetGameObject()->GetTransform().Forward().Normalized() * touches[0].deltaPosition.y * _cameraSpeed * deltaTime;
            GetGameObject()->GetTransform().Position -= GetGameObject()->GetTransform().Right().Normalized() * touches[0].deltaPosition.x * _cameraSpeed * deltaTime;

            Quaternion yaw = Quaternion::Rotation(-touches[1].deltaPosition.x * _mouseSensitivity.x, Vector3::up());
            GetGameObject()->GetTransform().Rotation = yaw * GetGameObject()->GetTransform().Rotation; // yaw on the left.
            // Pitch happens "under" the current rotation, in local coordinates.
            Quaternion pitch = Quaternion::Rotation(-touches[1].deltaPosition.y * _mouseSensitivity.y, Vector3::right());
            GetGameObject()->GetTransform().Rotate(pitch); // pitch on the right.
        }
		#endif
	}

	Component* FpsCamera::Copy()
	{
		return new FpsCamera(*this);
	}
}