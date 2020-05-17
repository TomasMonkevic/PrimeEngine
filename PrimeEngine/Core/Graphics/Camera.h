#pragma once

#include <Math/Math.h>
#include <Graphics/Shader/Shader.h>
#include <GameObject.h>
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Camera : public GameObject
	{
	private: //Variables
		Math::Matrix4x4 _projectionMatrix;
		Math::Matrix4x4 _viewMatrix = Math::Matrix4x4::identity();

	public:
		Camera(const Math::Matrix4x4& projectionMatrix);
		~Camera(); //camera should delete shader

		Math::Vector3 ScreenToWorldPoint(const Math::Vector2& point) const; //TEST
		Math::Vector2 ScreenToViewPoint(const Math::Vector2& point) const; //TEST

		Math::Vector2 ViewportToScreenPoint(const Math::Vector2& point) const; //TEST
		Math::Vector3 ViewportToWorldPoint(const Math::Vector2& point) const; //TEST

		Math::Vector2 WorldToScreenPoint(const Math::Vector3& point) const; //TEST
		Math::Vector2 WorldToViewPoint(const Math::Vector3& point) const; //TEST

		const Math::Matrix4x4& GetProjectionMatrix() const { return _projectionMatrix; }
		const Math::Matrix4x4& GetViewMatrix();

	};

}}