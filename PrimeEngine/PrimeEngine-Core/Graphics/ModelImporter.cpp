#include "ModelImporter.h"
#include "../Utilities/File.h"
#include "../Utilities/Log.h"
#include "../Utilities/Utils.h"
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

namespace PrimeEngine { namespace Graphics {
	
	void InsertVertex(std::vector<Graphics::TempVertexData>& vertices, std::vector<unsigned short>& indices,
		std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet)
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
				indexSet.normalIndex == 0 ? Math::Vector3::zero() : inputVertices.normals[indexSet.normalIndex - 1] };
			vertices.push_back(vertex);
		}
	}

	ModelImporter::ModelImporter()
	{
	}

	Mesh* ModelImporter::ImportModel(const char* path, bool isCalcTangents) const
	{
		using namespace PrimeEngine::Math;

		std::vector<std::string> lines = SplitString(File::ReadFile(path), "\n");
		if (lines.empty())
		{
			return nullptr;
		}

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
					#ifdef WIN_32
						int result = sscanf_s(cstr, "%*s %f %f", &uv.x, &uv.y);
					#else
						int result = sscanf(cstr, "%*s %f %f", &uv.x, &uv.y);
					#endif
					if (result == 0)
						continue;
					vertexSet->uvs.push_back(uv);
				}
				else if (strstr(cstr, "vn"))
				{
					Vector3 normal;
					#ifdef WIN_32
						int result = sscanf_s(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
					#else
						int result = sscanf(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
					#endif
					if (result == 0)
						continue;
					vertexSet->normals.push_back(normal);
				}
				else
				{
					Vector3 position;
					#ifdef WIN_32
						int result = sscanf_s(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
					#else
						int result = sscanf(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
					#endif
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
					if (indexes.size() == 1)
					{
						face[i - 1].positionIndex = stoi(indexes[0]);
						face[i - 1].uvIndex = 0;
						face[i - 1].normalIndex = 0;
					}
					else if (indexes.size() == 2)
					{
						face[i - 1].positionIndex = stoi(indexes[0]);
						if (strstr(tokens[i].c_str(), "//"))
						{
							face[i - 1].uvIndex = 0;
							face[i - 1].normalIndex = stoi(indexes[1]);
						}
						else
						{
							face[i - 1].uvIndex = stoi(indexes[1]);
							face[i - 1].normalIndex = 0;
						}
					}
					else
					{
						face[i - 1].positionIndex = stoi(indexes[0]);
						face[i - 1].uvIndex = stoi(indexes[1]);
						face[i - 1].normalIndex = stoi(indexes[2]);
					}
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
		return new Mesh(vertices.data(), sizeof(TempVertexData) * vertices.size(), indices.data(), indices.size());
	}
}}
