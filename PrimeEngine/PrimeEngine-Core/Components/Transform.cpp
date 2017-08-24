#include "Transform.h"
#include <Utilities\Log.h>

namespace PrimeEngine {

	Transform::Transform() :
		Transform(Math::Vector3::zero())
	{

	}

	Transform::Transform(const Math::Vector3& position) :
		Position(position)
	{
		AddType<Transform>();
	}

	Transform::~Transform()
	{
		PRIME_WARNING("trans dest is here \n");
	}
}

