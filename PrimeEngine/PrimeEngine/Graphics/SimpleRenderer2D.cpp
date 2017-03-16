#include "SimpleRenderer2D.h"

namespace PrimeEngine { namespace Graphics {

	SimpleRenderer2D::SimpleRenderer2D()
	{
		_renderQueue = new std::queue<const Renderable2D*>;
	}

	SimpleRenderer2D::~SimpleRenderer2D()
	{
		delete _renderQueue;
	}

	void SimpleRenderer2D::Submit(const Renderable2D* renderable2D)
	{
		_renderQueue->push(renderable2D);
	}

	void SimpleRenderer2D::Flush()
	{
		while (!_renderQueue->empty())
		{
			const Renderable2D* renderable2D = _renderQueue->front();
			if (renderable2D)
			{
				renderable2D->GetVertexArray()->Bind();
				renderable2D->GetIndexBuffer()->Bind();
				renderable2D->GetShader().SetUniform("model_matrix", renderable2D->GetModelMatrix());
				glDrawElements(GL_TRIANGLES, renderable2D->GetIndexBuffer()->GetCount(), GL_UNSIGNED_SHORT, 0);
				renderable2D->GetVertexArray()->Unbind();
				renderable2D->GetIndexBuffer()->Unbind();
				_renderQueue->pop();
			}
		}
	}

}}