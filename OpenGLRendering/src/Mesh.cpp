#include "Mesh.h"

void Mesh::AddVertex(float x, float y, float z)
{
	mVertices.emplace_back(x);
	mVertices.emplace_back(y);
	mVertices.emplace_back(z);
}

void Mesh::AddVertices(const std::initializer_list<float>& vertices)
{
	mVertices.insert(mVertices.end(), vertices);
}

void Mesh::AddIndex(const unsigned int index)
{
	mIndices.emplace_back(index);
}

void Mesh::AddIndices(const std::initializer_list<unsigned int>& indices)
{
	mIndices.insert(mIndices.end(), indices);
}

const float* Mesh::GetVertexData() const
{
	return mVertices.data();
}

const unsigned int* Mesh::GetIndexData() const
{
	return mIndices.data();
}

size_t Mesh::IndicesSize() const
{
	return mIndices.size();
}

size_t Mesh::VerticesSize() const
{
	return mVertices.size();
}