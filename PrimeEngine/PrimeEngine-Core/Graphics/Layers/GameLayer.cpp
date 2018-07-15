#include "GameLayer.h"

namespace PrimeEngine { namespace Graphics {

	GameLayer::GameLayer(Shader* shader, Camera* camera)
		: Layer(new BatchRenderer2D(), shader, camera)
	{
	}
}}