#include "Layer.h"
#include "../Texture.h"

namespace PrimeEngine { namespace Graphics {

	Layer::Layer(Renderer2D* renderer, Camera* _camera)
		: _renderer(renderer), camera(_camera)
	{
		_renderables = new std::vector<Object*>;
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

	void Layer::Submit(Object* object)
	{
		if (!_renderables->empty())
		{
			for (int i = 0; i < _renderables->size(); i++)
			{
				if (object->Priority <= _renderables->at(i)->Priority)
				{
					_renderables->insert(_renderables->begin() + i, object);
					break;
				}
			}
		}
		else
		{
			_renderables->push_back(object);
		}
	}

	void Layer::Remove(Object* object)
	{
		for (std::size_t i = 0; i < _renderables->size(); i++)
		{
			if ((*_renderables)[i] == object)
			{
				_renderables->erase(_renderables->begin() + i);
				return;
			}
		}
	}

	void Layer::Render()
	{
		camera->Render();
		camera->_shader->Enable();
		_renderer->Begin();
		for (const Object* renderable : *_renderables)
		{
			renderable->Submit(_renderer);
		}
		_renderer->End();
		_renderer->Flush();
		//TODO shady stuff here
		//camera->_shader->Disable();
	}
}}