#include "MeshRenderer.h"

namespace PrimeEngine { namespace Graphics {

	MeshRenderer::MeshRenderer(Mesh* mesh, Material* material)
		: _mesh(mesh), _material(material)
	{
		AddType<MeshRenderer>();
	}

	MeshRenderer::~MeshRenderer()
	{
		delete _mesh;
		//material isn't deleted for reusability
	}

	void MeshRenderer::Draw(const Camera& camera)
	{
		_material->Enable(camera, *GetGameObject());
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