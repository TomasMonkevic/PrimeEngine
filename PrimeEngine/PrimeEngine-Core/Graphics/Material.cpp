#include "Material.h"
#include <Math\Math.h>

namespace PrimeEngine { namespace Graphics {
	
	void Material::Enable(const Camera& camera, const GameObject& gameObject, const std::vector<Light*>& lights) const
	{
		_shader->Enable();
		//_shader->SetUniform("pointLightsCount", PointLight::Count());
		for (unsigned i=0;i<lights.size(); i++)
		{
			lights[i]->Enable(*_shader, i);
		}

		_shader->SetUniform("diffuseTexture", 0);
		_shader->SetUniform("specularTexture", 1);
		_shader->SetUniform("normalTexture", 2);

		_shader->SetUniform("diffuseColor", _diffuseColor);
		_shader->SetUniform("smoothness", _smoothness);

		_shader->SetUniform("viewPosition", camera.GetTransform().Position);
		_shader->SetUniform("pr_matrix", camera.GetProjectionMatrix());
		_shader->SetUniform("view_matrix", camera.GetViewMatrix());
		_shader->SetUniform("model_matrix", gameObject.GetTransform().GetModelMatrix());

		_diffuseMap->Activate(0);
		_diffuseMap->Bind();

		_specularMap->Activate(1);
		_specularMap->Bind();

		_normalMap->Activate(2);
		_normalMap->Bind();
	}

	void Material::Disable() const
	{
		//unbind texture?
		_shader->Disable();
	}

	Material::Material(const char* shaderSource, Texture* diffMap, Texture* specMap, const Color& color, float smoothness)
		: _shader(new Shader(shaderSource, true)), _diffuseMap(diffMap),
		_specularMap(specMap), _diffuseColor(color), _smoothness(smoothness)
	{

	}

	Material::Material(const char* shaderSource, const Color& color)
		: Material(shaderSource, new Texture(Color::white), new Texture(Color::white), color, 64)
	{

	}

	Material::Material(const char* shaderSource, Texture* diffMap, Texture* specMap)
		: Material(shaderSource, diffMap, specMap ? specMap : new Texture(Color::white), Color::white, 64)
	{

	}

	Material::~Material()
	{
		delete _shader;
		delete _diffuseMap;
		delete _specularMap;
		delete _normalMap;
	}
} }