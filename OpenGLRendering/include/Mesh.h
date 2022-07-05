#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <initializer_list>

#include <glad/glad.h>

class Mesh {
private:
	std::vector<float> mVertices{};
	std::vector<unsigned int> mIndices{};

public:
	void AddVertex(float x, float y, float z);
	void AddVertices(const std::initializer_list<float>& vertices);
	void AddIndex(const unsigned int index);
	void AddIndices(const std::initializer_list<unsigned int>& indices);
	const float* GetVertexData() const;
	const unsigned int* GetIndexData() const;

	size_t IndicesSize() const;
	size_t VerticesSize() const;
};