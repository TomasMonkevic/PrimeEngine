#include "GameLayer.h"

namespace PrimeEngine { namespace Graphics {

	GameLayer::GameLayer(Camera* camera)
		: Layer(new BatchRenderer2D(), camera)
	{
	}
}}