#include "UILayer.h"
#include <Math\Math.h>

namespace PrimeEngine { namespace Graphics {

	UILayer::UILayer()
		: Layer(new BatchRenderer2D(), new Shader(Shader::default, true), new Camera(Math::Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)))
	{
		_camera->LookAt(_camera->GetTransform().Position + Math::Vector3::forward());
	}

}}