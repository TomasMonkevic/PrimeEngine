#pragma once

#include <DllExport.h>
#include "Component.h"
#include <Math/Math.h>

namespace PrimeEngine {

	class PRIMEENGINEAPI Transform : public Component
	{
	public:
		//vector of child Transforms

		Math::Vector3 Position;
		Math::Quaternion Rotation = Math::Quaternion::identity(); //change to quaternion
		Math::Vector3 Scale = Math::Vector3::one();

	public:
		Transform();
		Transform(const Math::Vector3& position);
		~Transform() override;

		void AddChild();
		void RemoveChild();

		void LookAt(const Math::Vector3& target);
		inline void LookAt(const Transform& target) { LookAt(target.Position); }

		void Rotate(const Math::Quaternion& rotation) //TODO change rotation
		{
			Rotation *= rotation;
		}

		Math::Vector3 Forward() const
		{
			const Math::Matrix4x4 mat = Rotation.RotationMatrix();
			return mat[2];
		}

		Math::Vector3 Right() const
		{
			const Math::Matrix4x4 mat = Rotation.RotationMatrix();
			return mat[0];
		}

		Math::Vector3 Up() const
		{
			const Math::Matrix4x4 mat = Rotation.RotationMatrix();
			return mat[1];
		}

		inline Math::Matrix4x4 GetModelMatrix() const
		{
			return Math::Matrix4x4::TRS(Position, Rotation, Scale);
		}

		Component* Copy() override;
	};
}
