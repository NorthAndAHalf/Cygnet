#include "Model.h"
#include "spdlog/spdlog.h"

Model::Model(aiMesh* aim, glm::vec3 _pos, glm::vec3 _rot, float _scale)
	: pos(_pos), rot(_rot), scale(_scale)
{
	for (int i = 0; i < aim->mNumVertices; i++)
	{
		float x = aim->mVertices[i].x;
		float y = aim->mVertices[i].y;
		float z = aim->mVertices[i].z;
		glm::vec3 v = glm::vec3(x, y, z);
		vertices.push_back(v);
	}

	for (int i = 0; i < aim->mNumFaces; i++)
	{
		indices.push_back(aim->mFaces[i].mIndices[2]);
		indices.push_back(aim->mFaces[i].mIndices[1]);
		indices.push_back(aim->mFaces[i].mIndices[0]);
	}
}

Model::Model(const aiScene* ais, glm::vec3 _pos, glm::vec3 _rot, float _scale)
	: pos(_pos), rot(_rot), scale(_scale)
{
	unsigned int previousVertices = 0;
	for (int n = 0; n < ais->mNumMeshes; n++)
	{
		aiMesh* aim = ais->mMeshes[n];

		for (int i = 0; i < aim->mNumVertices; i++)
		{
			float x = aim->mVertices[i].x;
			float y = aim->mVertices[i].y;
			float z = aim->mVertices[i].z;
			glm::vec3 v = glm::vec3(x, y, z);
			vertices.push_back(v);
		}

		for (int i = 0; i < aim->mNumFaces; i++)
		{
			indices.push_back(aim->mFaces[i].mIndices[2] + previousVertices);
			indices.push_back(aim->mFaces[i].mIndices[1] + previousVertices);
			indices.push_back(aim->mFaces[i].mIndices[0] + previousVertices);
		}
		previousVertices += aim->mNumVertices;
	}
}

// For debugging
void Model::Print()
{
	spdlog::trace("Vertices:");
	for (glm::vec3 v : vertices)
	{
		spdlog::trace(std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z));
	}
	spdlog::trace("-------------------------------------------------------------------------");
	for (unsigned int i : indices)
	{
		spdlog::trace(i);
	}
}
