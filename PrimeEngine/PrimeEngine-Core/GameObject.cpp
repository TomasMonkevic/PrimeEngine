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
#include <memory>

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
				indexSet.positionIndex == 0 ? Math::Vector3::zero() : inputVertices.positions[indexSet.positionIndex - 1],
				0xFFFFFFFF,
				indexSet.uvIndex == 0 ? Math::Vector2::zero() : inputVertices.uvs[indexSet.uvIndex - 1],
				indexSet.normalIndex == 0 ? Math::Vector3::zero() :inputVertices.normals[indexSet.normalIndex - 1] };
			vertices.push_back(vertex);
		}
	}

	GameObject* GameObject::LoadObjModel(std::string path, bool isCalcTangents)
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

		unsigned progress = 1;
		for (std::string& line : lines)
		{
			if (progress == 4661)
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
				std::vector<std::string> tokens = SplitString(line, " ");
				if (tokens.size() < 4)
				{
					continue;
				}
				std::unique_ptr<IndexSet[]> face(new IndexSet[tokens.size() - 1]);
				for (unsigned i = 1; i < tokens.size(); i++)
				{
					std::vector<std::string> indexes = SplitString(tokens[i], "/");
					face[i-1].positionIndex = indexes.size() > 0 && !indexes[0].empty() ? stoi(indexes[0]) : 0;
					face[i-1].uvIndex = indexes.size() > 1 && !indexes[1].empty() ? stoi(indexes[1]) : 0;
					face[i-1].normalIndex = indexes.size() > 2 && !indexes[2].empty() ? stoi(indexes[2]) : 0;
				}

				InsertVertex(vertices, indices, mapping, *vertexSet, face[0]);
				InsertVertex(vertices, indices, mapping, *vertexSet, face[1]);
				InsertVertex(vertices, indices, mapping, *vertexSet, face[2]);

				if (tokens.size() - 1 == 4) //is the face quad
				{
					InsertVertex(vertices, indices, mapping, *vertexSet, face[0]);
					InsertVertex(vertices, indices, mapping, *vertexSet, face[2]);
					InsertVertex(vertices, indices, mapping, *vertexSet, face[3]);
				}
			}
			//PRIME_INFO(i, "\n");
			progress++;
		}
		if (isCalcTangents)
		{
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