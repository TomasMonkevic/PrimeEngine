#pragma once

#include <DllExport.h>
#include "Component.h"
#include <Math\Math.h>

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

		void Rotate(const Math::Quaternion& rotation) //TODO change rotation
		{
			Rotation = rotation;
		}

		inline const Math::Matrix4x4 GetModelMatrix() const
		{
			return Math::Matrix4x4::TRS(Position, Rotation, Scale);
		}
	};
}
