#include "Transform.h"
#include <Utilities/Log.h>

namespace PrimeEngine {

	Transform::Transform() :
		Transform(Math::Vector3::zero())
	{

	}

	Transform::Transform(const Math::Vector3& position) :
		Position(position)
	{
		AddType<Transform>();
	}

	Transform::~Transform()
	{
	}

	void Transform::LookAt(const Math::Vector3& target)
	{
		Math::Vector3 _direction = (Position - target).Normalized() * -1.0f;
		Math::Vector3 _right = Math::Vector3::Cross(Math::Vector3::up(), _direction).Normalized();
		Math::Vector3 _up = Math::Vector3::Cross(_direction, _right).Normalized();
		Math::Matrix4x4 tempMatrix = Math::Matrix4x4::identity();
		tempMatrix.SetRow(0, Math::Vector4(_right.x, _right.y, _right.z, 0));
		tempMatrix.SetRow(1, Math::Vector4(_up.x, _up.y, _up.z, 0));
		tempMatrix.SetRow(2, Math::Vector4(_direction.x, _direction.y, _direction.z, 0));
		Rotation = Math::Quaternion(tempMatrix);
	}

	Component* Transform::Copy()
	{
		return (new Transform(*this));
	}
}

