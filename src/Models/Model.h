#pragma once

#include "assimp/scene.h"
#include "glm/vec3.hpp"
#include <vector>

// --- Rotations are stored as a vec3, each component is a rotation in radians around that axis ---

class Model
{
public:
	Model(aiMesh* aim, glm::vec3 _pos, glm::vec3 _rot, float _scale);
	Model(const aiScene* ais, glm::vec3 _pos, glm::vec3 _rot, float _scale); // Combines all aiMesh objects from one aiScene into one Model

	const std::vector<glm::vec3>& GetVertices() const { return vertices; }
	const std::vector<unsigned int>& GetIndices() const { return indices; }

	void Print();

	glm::vec3 pos;
	glm::vec3 rot;
	float scale;
private:
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
};

// Generate one model for each mesh in an aiScene
//bool GenerateModelVector(std::vector<Model>& out, aiScene* ais, glm::vec3 _pos, glm::vec3 _rot, float _scale);