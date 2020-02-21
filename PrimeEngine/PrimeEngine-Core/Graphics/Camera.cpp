#include "Camera.h"

#include <Graphics/BasicWindow.h>

namespace PrimeEngine { namespace Graphics {

	Camera::Camera(const Math::Matrix4x4& projectionMatrix) :
		 _projectionMatrix(projectionMatrix)
	{
	}

	Camera::~Camera()
	{
	}

	Math::Vector3 Camera::ScreenToWorldPoint(const Math::Vector2& point) const
	{
		Math::Vector2 viewPort = ScreenToViewPoint(point);
		Math::Matrix4x4 viewProjectionInverse = (_projectionMatrix * _viewMatrix).Inverse();
		Math::Vector3 point3D(viewPort.x, viewPort.y, 0);
		return Math::Matrix4x4::Multiply(viewProjectionInverse, point3D);
	}

	Math::Vector2 Camera::ScreenToViewPoint(const Math::Vector2& point) const
	{
		Math::Vector2 screenSize = GetWindow()->GetSize();
		return Math::Vector2(2.0f * point.x / screenSize.x - 1, -2.0f * point.y / screenSize.y + 1);
	}

	Math::Vector2 Camera::ViewportToScreenPoint(const Math::Vector2& point) const
	{
		Math::Vector2 screenSize = GetWindow()->GetSize();
		return Math::Vector2((screenSize.x * (point.x + 1)) / 2.0f, (screenSize.y * (point.y - 1)) / -2.0f );
	}

	Math::Vector3 Camera::ViewportToWorldPoint(const Math::Vector2& point) const
	{
		return ScreenToWorldPoint(ViewportToScreenPoint(point));
	}

	Math::Vector2 Camera::WorldToScreenPoint(const Math::Vector3& point) const
	{
		return ViewportToScreenPoint(WorldToViewPoint(point)); //and then viewPort to screen
	}

	Math::Vector2 Camera::WorldToViewPoint(const Math::Vector3& point) const
	{
		return _projectionMatrix * _viewMatrix * point;
	}

	const Math::Matrix4x4& Camera::GetViewMatrix()
	{
		Math::Matrix4x4 temp = GetTransform().Rotation.RotationMatrix();
		temp[2] = temp[2] * -1; //inverse the z axis
		_viewMatrix = (Math::Matrix4x4::Transform(GetTransform().Position) * temp * Math::Matrix4x4::Scale(GetTransform().Scale)).Inverse();
		return _viewMatrix;
	}
}}