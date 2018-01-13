#include "MeshRenderer.h"

namespace PrimeEngine { namespace Graphics {

	MeshRenderer::MeshRenderer(Mesh* mesh, Shader* shader)
		: _mesh(mesh), _material(shader)
	{
		_texture = new Texture("Resources/Textures/boxDiff.png");
		AddType<MeshRenderer>();
	}

	MeshRenderer::~MeshRenderer()
	{
		delete _mesh;
		delete _texture;
	}

	void MeshRenderer::Draw(const Camera& camera)
	{
		_material->Enable();

		//TODO move this to material class
		_material->SetUniform("light.position", Vector3(5.0f, 5.0f, 2.0f));
		//_material->SetUniform("light.color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		_material->SetUniform("light.color", Vector4::one());
		_material->SetUniform("light.intensity", 0.4f);
		_material->SetUniform("diffuseTexture", 0);
		//-----------------------

		_material->SetUniform("viewPosition", camera.GetTransform().Position);
		_material->SetUniform("pr_matrix", camera.GetProjectionMatrix());
		_material->SetUniform("view_matrix", camera.GetViewMatrix());
		_material->SetUniform("model_matrix", GetGameObject()->GetTransform().GetModelMatrix());

		_texture->Activate(0);
		_texture->Bind();


		_mesh->Bind();
		glDrawElements(GL_TRIANGLES, _mesh->GetIndexCount(), GL_UNSIGNED_SHORT, NULL);
		_mesh->Unbind();
		//unbind texture?
		_material->Disable();
	}

	Component* MeshRenderer::Copy()
	{
		return (new MeshRenderer(*this));
	}
}}