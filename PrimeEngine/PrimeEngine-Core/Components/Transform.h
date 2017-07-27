#pragma once

#include <DllExport.h>
#include "Component.h"
#include <Math\Math.h>

namespace PrimeEngine {

	class PRIMEENGINEAPI Transform : public Component
	{
	private:
		//vector of child Transforms

		Math::Vector3 _position;
		Math::Matrix4x4 _rotationMatrix = Math::Matrix4x4::identity(); //change to quaternion
		Math::Vector3 _scale = Math::Vector3::one();

	public:
		explicit Transform();
		explicit Transform(const Math::Vector3& position);
		~Transform() override;

		void AddChild();
		void RemoveChild();

		void Rotate(float angle, const Math::Vector3& axis) //change to quaternion
		{
			_rotationMatrix *= Math::Matrix4x4::Rotate(angle, axis);
		}

		inline void SetPosition(const Math::Vector3& position)
		{
			_position = position;
		}

		inline void SetScale(const Math::Vector3& scale)
		{
			_scale = scale;
		}

		inline const Math::Matrix4x4 GetModelMatrix() const
		{
			return Math::Matrix4x4::TRS(_position, _rotationMatrix, _scale);
		}

		inline const Math::Vector3& GetPosition() const
		{
			return _position;
		}
	};
}
