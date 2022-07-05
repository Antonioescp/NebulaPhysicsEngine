#pragma once

#include <Mesh.h>
#include <Shader.h>
#include <string>

import Core;

class MeshRenderer 
{
private:
	Mesh mMesh;
	Shader mShader;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void Bind();
	void Buffer();

public:
	Nebula::Core::Vector3 position;
	Nebula::Core::Vector3 scale;
	glm::vec3 color;
	glm::mat4 view;
	glm::mat4 projection;

	~MeshRenderer();
	MeshRenderer(const Mesh& mesh, const std::string& vertexPath, const std::string& fragPath);
	void Draw();
	void SetMesh(Mesh mesh);
	void SetShader(const std::string& vertexPath, const std::string& fragPath);
};