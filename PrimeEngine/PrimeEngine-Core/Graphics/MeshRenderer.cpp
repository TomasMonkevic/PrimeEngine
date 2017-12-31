#include "MeshRenderer.h"

namespace PrimeEngine { namespace Graphics {

	MeshRenderer::MeshRenderer(Mesh* mesh, Shader* shader)
		: _mesh(mesh), _material(shader)
	{
		AddType<MeshRenderer>();
	}

	MeshRenderer::~MeshRenderer()
	{
		delete _mesh;
	}

	void MeshRenderer::Draw(const Camera& camera)
	{
		_material->Enable();

		//TODO move this to material class
		_material->SetUniform("light.position", Vector3(5.0f, 5.0f, 2.0f));
		//_material->SetUniform("light.color", Vector4(1.0f, 0.0f, 0.0f, 1.0f)); //TODO this doesn't look good
		_material->SetUniform("light.color", Vector4::one());
		_material->SetUniform("light.intensity", 0.3f);
		_material->SetUniform("viewPosition", camera.GetTransform().Position);
		//-----------------------

		_material->SetUniform("pr_matrix", camera.GetProjectionMatrix());
		_material->SetUniform("view_matrix", camera.GetViewMatrix());
		_material->SetUniform("model_matrix", GetGameObject()->GetTransform().GetModelMatrix());

		_mesh->Bind();
		glDrawElements(GL_TRIANGLES, _mesh->GetIndexCount(), GL_UNSIGNED_SHORT, NULL);
		_mesh->Unbind();

		_material->Disable();
	}

	Component* MeshRenderer::Copy()
	{
		return (new MeshRenderer(*this));
	}
}}