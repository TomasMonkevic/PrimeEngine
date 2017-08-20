#ifndef CAMERA_H
#define CAMERA_H

#include <GL\glew.h>
#include <Math/Math.h>
#include <Graphics\Shader\Shader.h>
#include <DllExport.h>

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Camera
	{
	private: //Variables
		Math::Matrix4x4 _projectionMatrix;
		Math::Matrix4x4 _viewMatrix;
		Math::Vector3 _position;
		Math::Vector3 _direction;
		Math::Vector3 _right;
		Math::Vector3 _up;
	public:
		Shader* _shader;

	private: //Methods

	public:
		Camera(Shader* shader, const Math::Matrix4x4& projectionMatrix);
		~Camera(); //camera should delete shader

		Math::Vector3 ScreenToWorldPoint(const Math::Vector2& point) const; //TEST
		Math::Vector2 ScreenToViewPoint(const Math::Vector2& point) const; //TEST

		Math::Vector2 ViewportToScreenPoint(const Math::Vector2& point) const; //TEST
		Math::Vector3 ViewportToWorldPoint(const Math::Vector2& point) const; //TEST

		Math::Vector2 WorldToScreenPoint(const Math::Vector3& point) const; //TEST
		Math::Vector2 WorldToViewPoint(const Math::Vector3& point) const; //TEST

		void LookAt(const Math::Vector3& target);
		void Render();

		inline const Math::Vector3& GetPosition() const { return _position; }
		inline void SetPosition(const Math::Vector3& position) { _position = position; }
	};

}}
#endif // !CAMERA_H
