#include "Group.h"

namespace PrimeEngine { namespace Graphics {

	Group::Group(const Math::Vector3& position, const Math::Vector2& size)
		: Renderable2D(position, size, NULL, Color::black)
	{
		_children = new std::vector<Renderable2D*>;
	}

	Group::~Group()
	{
		delete _children;
	}

	void Group::Add(Renderable2D* child)
	{
		_children->push_back(child);
	}

	void Group::Submit(Renderer2D* renderer) const
	{
		renderer->PushMatrix(GetModelMatrix());
		for (const Renderable2D* child : *_children)
		{
			child->Submit(renderer);
		}
		renderer->PopMatrix();
	}

	void Group::Remove(Renderable2D* child)
	{
		for (std::size_t i = 0; i < _children->size(); i++)
		{
			if ((*_children)[i] == child)
			{
				_children->erase(_children->begin() + i);
				return;
			}
		}
	}
}}