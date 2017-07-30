#include "UILayer.h"
#include <Math\Math.h>

namespace PrimeEngine { namespace Graphics {

	UILayer::UILayer(Shader* shader)
		: Layer(new BatchRenderer2D(), new Camera(shader, Math::Matrix4x4::Orthographic(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f)))
	{
		camera->SetPosition(Math::Vector3::zero());
		camera->LookAt(camera->GetPosition() + Math::Vector3::back());
	}

}}