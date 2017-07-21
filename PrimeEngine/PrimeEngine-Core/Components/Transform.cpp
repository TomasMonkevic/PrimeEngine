#include "Transform.h"
#include <Utilities\Log.h>

namespace PrimeEngine {

	Transform::Transform() :
		Transform(Math::Vector3::zero())
	{

	}

	Transform::Transform(const Math::Vector3& position) :
		_position(position)
	{

	}

	Transform::~Transform()
	{
		PRIME_WARNING("trans dest is here \n");
	}
}

