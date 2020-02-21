#include "Layer.h"
#include "../Texture.h"

namespace PrimeEngine { namespace Graphics {

	Layer::Layer(Renderer2D* renderer, Shader* shader, Camera* camera)
		: _renderer(renderer), _shader(shader), _camera(camera)
	{
		_renderables = new std::vector<Object*>;
		GLint texIds[MAX_TEXTURE_COUNT]; //should be moved somewhere else? yes
		for (unsigned i = 0; i < MAX_TEXTURE_COUNT; i++)
		{
			texIds[i] = i;
		} //----------

		_shader->Enable();
		_shader->SetUniform("textures", texIds, MAX_TEXTURE_COUNT);
		_shader->Disable();
	}

	Layer::~Layer() //don't take control of renderables
	{
		//for (int i = 0; i < _renderables->size(); i++)
		//{
		//	delete (*_renderables)[i];
		//}
		delete _renderables;
		delete _renderer;
		delete _shader;
		delete _camera;
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
		_shader->Enable();
		//Needed for android on the default shader
		_shader->SetUniform("model_matrix", Math::Matrix4x4::identity());
		_shader->SetUniform("pr_matrix", _camera->GetProjectionMatrix());
		_shader->SetUniform("view_matrix", _camera->GetViewMatrix());
		_renderer->Begin();
		for (const Object* renderable : *_renderables)
		{
			renderable->Submit(_renderer);
		}
		_renderer->End();
		_renderer->Flush();
		_shader->Disable();
	}
}}