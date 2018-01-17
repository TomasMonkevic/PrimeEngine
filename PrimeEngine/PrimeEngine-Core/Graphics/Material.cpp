#include "Material.h"
#include <Math\Math.h>

namespace PrimeEngine { namespace Graphics {
	
	void Material::Enable(const Camera& camera, const GameObject& gameObject) const
	{
		_shader->Enable();
		_shader->SetUniform("light.position", Vector3(5.0f, 5.0f, 2.0f));
		//_shader->SetUniform("light.color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		_shader->SetUniform("light.color", Vector4::one());
		_shader->SetUniform("light.intensity", 0.25f);
		_shader->SetUniform("light.range", 25.0f);

		_shader->SetUniform("diffuseTexture", 0);
		_shader->SetUniform("specularTexture", 1);
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
	}

	void Material::Disable() const
	{
		_shader->Disable();
	}

	Material::Material(const char* shaderSource, Texture* diffMap, Texture* specMap, const Color& color, float smoothness)
		: _shader(new Shader(shaderSource, true)), _diffuseMap(diffMap),
		_specularMap(specMap), _diffuseColor(color), _smoothness(smoothness)
	{

	}

	Material::Material(const char* shaderSource, const Color& color)
		: Material(shaderSource, new Texture(), new Texture(), color, 64)
	{

	}

	Material::Material(const char* shaderSource, Texture* diffMap, Texture* specMap)
		: Material(shaderSource, diffMap, specMap, Color::white, 64)
	{

	}

	Material::~Material()
	{
		delete _shader;
		delete _diffuseMap;
		delete _specularMap;
	}
} }