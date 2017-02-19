#include "Camera.h"
#include "Window.h"

namespace PrimeEngine { namespace Graphics {

	Camera::Camera(const Shader& shader, const Math::Matrix4x4& projectionMatrix) :
		_shader(shader), _projectionMatrix(projectionMatrix)
	{
		_shader.SetUniform("pr_matrix", _projectionMatrix);
	}

	Math::Vector3 Camera::ScreenToWorldPoint(const Math::Vector2& position) const
	{
		Math::Vector2 screenSize = Window::GetWindow()->GetSize();
		float x = 2.0 * position.x / screenSize.x - 1;
		float y = -2.0 * position.y / screenSize.y + 1;
		Math::Matrix4x4 viewProjectionInverse = (_projectionMatrix * _viewMatrix).Inverse();
		Math::Vector3 point3D(x, y, 0);
		return Math::Matrix4x4::Multiply(viewProjectionInverse, point3D);
	}

	void Camera::LookAt(const Math::Vector3& target)
	{
		_direction = (_position - target).Normalized();
		_right = Math::Vector3::Cross(Math::Vector3::up, _direction).Normalized();
		_up = Math::Vector3::Cross(_direction, _right).Normalized();
		Math::Matrix4x4 tempMatrix = Math::Matrix4x4::identity;
		tempMatrix.SetRow(0, Math::Vector4(_right.x, _right.y, _right.z, 0));
		tempMatrix.SetRow(1, Math::Vector4(_up.x, _up.y, _up.z, 0));
		tempMatrix.SetRow(2, Math::Vector4(_direction.x, _direction.y, _direction.z, 0));
		_viewMatrix =  tempMatrix * Math::Matrix4x4::Transform(_position * -1);
	}

	void Camera::Render()
	{
		_shader.SetUniform("view_matrix", _viewMatrix);
	}

}}