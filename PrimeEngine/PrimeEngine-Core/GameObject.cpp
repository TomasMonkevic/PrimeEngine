#include "GameObject.h"
#include <Graphics\Renderable.h>
#include <Graphics\Sprite.h>
#include <Graphics\Label.h>
#include "Utilities\File.h"
#include "Utilities\Utils.h"
#include "Graphics\Mesh.h"
#include "Graphics\Material.h"
#include "Graphics\MeshRenderer.h"
#include <unordered_map>

struct IndexSet
{
	int positionIndex;
	int uvIndex;
	int normalIndex;

	bool operator!=(const IndexSet& right) const
	{
		return !(*this == right);
	}

	bool operator==(const IndexSet& right) const
	{
		if (positionIndex != right.positionIndex) return false;
		if (uvIndex != right.uvIndex) return false;
		if (normalIndex != right.normalIndex) return false;
		return true;
	}
};

struct VertexSet
{
	std::vector<PrimeEngine::Math::Vector3> positions;
	std::vector<PrimeEngine::Math::Vector2> uvs;
	std::vector<PrimeEngine::Math::Vector3> normals;
};

template<>
struct std::hash<IndexSet>
{
	const size_t operator()(const IndexSet& key) const
	{
		return (key.positionIndex) ^ (key.normalIndex << 14) ^ (key.uvIndex << 23);
	}
};

namespace PrimeEngine {

	void InsertVertex(std::vector<Graphics::TempVertexData>& vertices, std::vector<unsigned short>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet)
	{
		auto lookup = mapping.find(indexSet);
		if (lookup != mapping.end())
		{
			indices.push_back(lookup->second);
		}
		else
		{
			mapping[indexSet] = (int)vertices.size();
			indices.push_back(vertices.size());
			Graphics::TempVertexData vertex = {
				inputVertices.positions[indexSet.positionIndex - 1],
				0xFFFFFFFF,
				inputVertices.uvs[indexSet.uvIndex - 1],
				inputVertices.normals[indexSet.normalIndex - 1] };
			vertices.push_back(vertex);
		}
	}

	GameObject* GameObject::LoadObjModel(std::string path)
	{
		using namespace PrimeEngine::Math;

		std::vector<std::string> lines = SplitString(File::ReadFile(path.c_str()), "\n");
		if (lines.empty())
		{
			return nullptr;
		}

		auto* result = new GameObject();
		VertexSet* vertexSet = new VertexSet;
		std::vector<Graphics::TempVertexData> vertices;
		std::vector<unsigned short> indices;
		std::unordered_map<IndexSet, int> mapping;

		unsigned i = 1;
		for (std::string& line : lines)
		{
			if (i == 4661)
			{
				PRIME_INFO("lol");
			}
			const char* cstr = line.c_str();
			if (strstr(cstr, "#")) // Comment
			{
				continue;
			}
			else if (strstr(cstr, "v"))
			{
				if (strstr(cstr, "vt"))
				{
					Vector2 uv;
					int result = sscanf_s(cstr, "%*s %f %f", &uv.x, &uv.y);
					if (result == 0)
						continue;
					vertexSet->uvs.push_back(uv);
				}
				else if (strstr(cstr, "vn"))
				{
					Vector3 normal;
					int result = sscanf_s(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
					if (result == 0)
						continue;
					vertexSet->normals.push_back(normal);
				}
				else
				{
					Vector3 position;
					int result = sscanf_s(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
					if (result == 0)
						continue;
					vertexSet->positions.push_back(position);
				}
			}
			else if (strstr(cstr, "f"))
			{
				IndexSet face[3];
				int result = sscanf_s(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
					&face[0].positionIndex, &face[0].uvIndex, &face[0].normalIndex,
					&face[1].positionIndex, &face[1].uvIndex, &face[1].normalIndex,
					&face[2].positionIndex, &face[2].uvIndex, &face[2].normalIndex);
				if (result == 0)
					continue;

				InsertVertex(vertices, indices, mapping, *vertexSet, face[0]);
				InsertVertex(vertices, indices, mapping, *vertexSet, face[1]);
				InsertVertex(vertices, indices, mapping, *vertexSet, face[2]);
			}
			//PRIME_INFO(i, "\n");
			i++;
		}
		for (int i = 0; i<indices.size(); i += 3)
		{
			Vector3 edge1 = vertices[indices[i + 1]].position - vertices[indices[i + 0]].position;
			Vector3 edge2 = vertices[indices[i + 2]].position - vertices[indices[i + 0]].position;
			Vector2 deltaUV1 = vertices[indices[i + 1]].uv - vertices[indices[i + 0]].uv;
			Vector2 deltaUV2 = vertices[indices[i + 2]].uv - vertices[indices[i + 0]].uv;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			Vector3 tangent(deltaUV2.y * edge1.x - deltaUV1.y * edge2.x, deltaUV2.y * edge1.y - deltaUV1.y * edge2.y, deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			tangent *= f;
			tangent.Normalized();

			vertices[indices[i + 0]].tangent = tangent;
			vertices[indices[i + 1]].tangent = tangent;
			vertices[indices[i + 2]].tangent = tangent;
		}
		Graphics::Mesh* mesh = new Graphics::Mesh(vertices.data(), sizeof(Graphics::TempVertexData) * vertices.size(), indices.data(), indices.size());
		Graphics::Material* material = new Graphics::Material(Graphics::Shader::simplePhong); //TODO also memory leak
		//Graphics::Material* material = new Graphics::Material(Graphics::Shader::phong, new Graphics::Texture("Resources/Textures/boxDiff.png"), new Graphics::Texture("Resources/Textures/boxSpec.png")); //TODO don't forget to delete this
		material->Smoothness() = 256.0f;
		result->AddComponent(new Graphics::MeshRenderer(mesh, material));
		delete vertexSet;
		PRIME_INFO("Loaded ", path.c_str(), '\n');
		return result;
	}

	GameObject::GameObject() :
		GameObject(Math::Vector3::zero())
	{

	}

	GameObject::GameObject(const Math::Vector3& position)
	{
		_components = new std::vector<Component*>;
		_children = new std::vector<GameObject*>; //TODO should children be in gameObject
		AddComponent(new Transform(position));
	}

	GameObject::GameObject(const GameObject& obj)
	{
		_components = new std::vector<Component*>;
		_children = new std::vector<GameObject*>; //TODO should children be in gameObject
		Priority = obj.Priority;
		for (int i = 0; i < obj._components->size(); i++) //for now only copy components
		{
			AddComponent(obj._components->at(i)->Copy());
		}
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < (*_components).size(); i++)
		{
			delete (*_components)[i];
		}
		delete _components;
		//TODO also delete all children???
		delete _children;
	}

	void GameObject::Add(GameObject* child)
	{
		_children->push_back(child);
	}

	void GameObject::Submit(Graphics::Renderer2D* renderer) const
	{
		Graphics::Renderable* sprite = GetComponent<Graphics::Renderable>();
		if (sprite)
		{
			sprite->Submit(renderer);
		}
		//could be added a local position and a global. better for performance
		renderer->PushMatrix(GetTransform().GetModelMatrix());
		for (const GameObject* child : *_children)
		{
			child->Submit(renderer);
		}
		renderer->PopMatrix();
	}
}