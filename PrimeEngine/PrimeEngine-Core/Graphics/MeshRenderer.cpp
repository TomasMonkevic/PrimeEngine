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
		//TODO maybe don't delete material?
		delete _material;
	}

	void MeshRenderer::Draw(const Camera& camera)
	{
		_material->Enable();
		_material->SetUniform("pr_matrix", camera.GetProjectionMatrix());
		_material->SetUniform("view_matrix", camera.GetViewMatrix());
		_material->SetUniform("model_matrix", GetGameObject()->GetTransform().GetModelMatrix());

		_mesh->Bind();
		glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, NULL);
		_mesh->Unbind();

		_material->Disable();
	}

	Component* MeshRenderer::Copy()
	{
		return (new MeshRenderer(*this));
	}
}}