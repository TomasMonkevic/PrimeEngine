#ifndef PRIME_RENDERER2D_H
#define PRIME_RENDERER2D_H

#include <vector>
#include <Graphics/Font.h>
#include "..\Core\Math.h"
#include "..\DllExport.h"

namespace PrimeEngine { namespace Graphics {

	class Renderable2D;
	class Label;

	class PRIMEENGINEAPI Renderer2D
	{
	protected:
		std::vector<Math::Matrix4x4>* _transformationStack;
		const Math::Matrix4x4* _transformationStackBack;

	protected:
		Renderer2D()
		{
			_transformationStack = new std::vector<Math::Matrix4x4>;
			_transformationStack->push_back(Math::Matrix4x4::identity);
			_transformationStackBack = &(_transformationStack->back());
		}

	public:
		virtual ~Renderer2D()
		{
			delete _transformationStack;
		}

		virtual void PushMatrix(const Math::Matrix4x4& traslationMat)
		{
			_transformationStack->push_back(*_transformationStackBack * traslationMat);
			_transformationStackBack = &_transformationStack->back();
		}

		virtual void PopMatrix()
		{
			if (_transformationStack->size() > 1)
			{
				_transformationStack->pop_back();
				_transformationStackBack = &_transformationStack->back();
			}
		}

		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable2D) = 0;
		virtual void DrawLabel(const std::string& text, const  Math::Vector3& position, const Font& font) = 0;
		virtual void End() {}
		virtual void Flush() = 0;
	};
}}

#endif // !PRIME_RENDERER2D_H