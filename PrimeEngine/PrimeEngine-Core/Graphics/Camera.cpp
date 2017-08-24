#include "Camera.h"
#include "Window.h"

namespace PrimeEngine { namespace Graphics {

	Camera::Camera(Shader* shader, const Math::Matrix4x4& projectionMatrix) :
		_shader(shader), _projectionMatrix(projectionMatrix)
	{
		_shader->Enable();
		_shader->SetUniform("pr_matrix", _projectionMatrix);
	}

	Camera::~Camera()
	{
		delete _shader;
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
		Math::Vector2 screenSize = Window::GetWindow()->GetSize();
		return Math::Vector2(2.0f * point.x / screenSize.x - 1, -2.0f * point.y / screenSize.y + 1);
	}

	Math::Vector2 Camera::ViewportToScreenPoint(const Math::Vector2& point) const
	{
		Math::Vector2 screenSize = Window::GetWindow()->GetSize();
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

	void Camera::LookAt(const Math::Vector3& target)
	{
		_direction = (_position - target).Normalized();
		_right = Math::Vector3::Cross(Math::Vector3::up(), _direction).Normalized();
		_up = Math::Vector3::Cross(_direction, _right).Normalized();
		Math::Matrix4x4 tempMatrix = Math::Matrix4x4::identity();
		tempMatrix.SetRow(0, Math::Vector4(_right.x, _right.y, _right.z, 0));
		tempMatrix.SetRow(1, Math::Vector4(_up.x, _up.y, _up.z, 0));
		tempMatrix.SetRow(2, Math::Vector4(_direction.x, _direction.y, _direction.z, 0));
		_viewMatrix =  tempMatrix * Math::Matrix4x4::Transform(_position * -1);
	}

	void Camera::Render()
	{
		_shader->SetUniform("view_matrix", _viewMatrix);
	}

}}