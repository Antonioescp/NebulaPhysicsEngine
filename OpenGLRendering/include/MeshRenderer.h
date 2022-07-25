#pragma once

#include <string>

#include <Mesh.h>
#include <Shader.h>
#include <Vector3.h>

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
	Nebula::Vector3 position;
	Nebula::Vector3 scale;
	glm::vec3 color;
	glm::mat4 view;
	glm::mat4 projection;

	~MeshRenderer();
	MeshRenderer(const Mesh& mesh, const std::string& vertexPath, const std::string& fragPath);
	void Draw();
	void SetMesh(Mesh mesh);
	void SetShader(const std::string& vertexPath, const std::string& fragPath);
};