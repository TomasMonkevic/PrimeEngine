#ifndef PRIME_GROUP_H
#define PRIME_GROUP_H

#include <vector>
#include "../Renderable2D.h"
#include "../../Math/Matrix4x4.h"
#include "../../DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class PRIMEENGINEAPI Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*>* _children;
		Math::Matrix4x4 _transformation;

	public:
		Group(const Math::Vector3& position, const Math::Vector2& size);
		~Group();

		void Add(Renderable2D* child);
		void Submit(Renderer2D* renderer) const override;
		void Remove(Renderable2D* child);
	};
}}

#endif // !PRIME_GROUP_H