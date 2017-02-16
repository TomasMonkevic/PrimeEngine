#ifndef CAMERA_H
#define CAMERA_H

#include <GL\glew.h>
#include "..\Core\Math.h"
#include "Shader.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Camera
	{
	private: //Variables
		Shader _shader;
		Math::Matrix4x4 _projectionMatrix;
		Math::Matrix4x4 _viewMatrix;
		Math::Vector3 _position;
		Math::Vector3 _direction;
		Math::Vector3 _right;
		Math::Vector3 _up;
	public:

	private: //Methods

	public:
		Camera(const Shader& shader, const Math::Matrix4x4& projectionMatrix);

		Math::Vector3 ScreenToWorldPoint(const Math::Vector2& position) const;

		void LookAt(const Math::Vector3& target);
		void Render();

		inline const Math::Vector3& GetPosition() const { return _position; }
		inline void SetPosition(const Math::Vector3& position) { _position = position; }
	};

}}
#endif // !CAMERA_H
