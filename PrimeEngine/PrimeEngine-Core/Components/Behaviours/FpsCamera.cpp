#include "FpsCamera.h"
#include <algorithm>

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
		//TODO refactor
        for(int i=0; i<std::min<unsigned int>(touches.size(), 2U); i++) {
            if(IsLeftSideTouch(touches[i].position)) {
                if(touches[i].phase == Input::TouchPhase::BEGAN) {
                    _positionTouchStartPosition = touches[i].position;
                }
                else if(touches[i].phase == Input::TouchPhase::ENDED) {
                    _positionTouchStartPosition = Math::Vector2::zero();
                }
                else {
                    Math::Vector2 delta = _positionTouchStartPosition - touches[i].position;
                    delta.x = std::max(-50.0f, std::min(delta.x, 50.0f));
                    delta.y = std::max(-50.0f, std::min(delta.y, 50.0f));
                    GetGameObject()->GetTransform().Position += GetGameObject()->GetTransform().Forward().Normalized() * delta.y * _cameraSpeed * deltaTime;
                    GetGameObject()->GetTransform().Position -= GetGameObject()->GetTransform().Right().Normalized() * delta.x * _cameraSpeed * deltaTime;
                }
            }
            else {
                if(touches[i].phase == Input::TouchPhase::BEGAN) {
                    _rotationTouchStartPosition = touches[i].position;
                }
                else if(touches[i].phase == Input::TouchPhase::ENDED) {
                    _rotationTouchStartPosition = Math::Vector2::zero();
                }
                else {
                    Math::Vector2 delta = _rotationTouchStartPosition - touches[i].position;
                    delta.x = std::max(-50.0f, std::min(delta.x, 50.0f));
                    delta.y = std::max(-50.0f, std::min(delta.y, 50.0f));
                    Quaternion yaw = Quaternion::Rotation(-delta.x * _mouseSensitivity.x, Vector3::up());
                    GetGameObject()->GetTransform().Rotation = yaw * GetGameObject()->GetTransform().Rotation; // yaw on the left.
                    // Pitch happens "under" the current rotation, in local coordinates.
                    Quaternion pitch = Quaternion::Rotation(-delta.y * _mouseSensitivity.y, Vector3::right());
                    GetGameObject()->GetTransform().Rotate(pitch); // pitch on the right.
                }
            }
        }
		#endif
	}

    bool FpsCamera::IsLeftSideTouch(Math::Vector2 position) {
	    // TODO get window size
        return position.x <= 1100;
	}

    Component* FpsCamera::Copy()
	{
		return new FpsCamera(*this);
	}
}