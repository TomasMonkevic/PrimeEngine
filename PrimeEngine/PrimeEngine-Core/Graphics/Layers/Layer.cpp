#include "Layer.h"

namespace PrimeEngine { namespace Graphics {

	Layer::Layer(Renderer2D* renderer, Camera* _camera)
		: _renderer(renderer), camera(_camera)
	{
		_renderables = new std::vector<Renderable2D*>;
		GLint texIds[MAX_TEXTURE_COUNT]; //should be moved somewhere else?
		for (unsigned i = 0; i < MAX_TEXTURE_COUNT; i++)
		{
			texIds[i] = i;
		} //----------
		camera->_shader->SetUniform("textures", texIds, MAX_TEXTURE_COUNT);
	}

	Layer::~Layer() //don't take control of renderables
	{
		//for (int i = 0; i < _renderables->size(); i++)
		//{
		//	delete (*_renderables)[i];
		//}
		delete _renderables;
		delete _renderer;
		delete camera;
	}

	void Layer::Submit(Renderable2D* renderable)
	{
		_renderables->push_back(renderable);
	}

	void Layer::Remove(Renderable2D* renderable)
	{
		for (std::size_t i = 0; i < _renderables->size(); i++)
		{
			if ((*_renderables)[i] == renderable)
			{
				_renderables->erase(_renderables->begin() + i);
				return;
			}
		}
	}

	void Layer::Render()
	{
		camera->_shader->Enable();
		_renderer->Begin();
		for (const Renderable2D* renderable : *_renderables)
		{
			renderable->Submit(_renderer);
		}
		_renderer->End();
		camera->Render();
		_renderer->Flush();
	}
}}