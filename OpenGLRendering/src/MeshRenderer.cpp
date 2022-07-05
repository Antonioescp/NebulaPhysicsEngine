#include <MeshRenderer.h>

MeshRenderer::MeshRenderer(const Mesh& mesh, const std::string& vertexPath, const std::string& fragPath)
	: mMesh{ mesh }, mShader{vertexPath, fragPath}, position{}, view{1.0f}, projection{1.0f}, scale{1.0f, 1.0f, 1.0f}
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	Buffer();
}

MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void MeshRenderer::Buffer()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mMesh.VerticesSize() * sizeof(float), mMesh.GetVertexData(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	if (mMesh.IndicesSize() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMesh.IndicesSize() * sizeof(unsigned int), mMesh.GetIndexData(), GL_STATIC_DRAW);
	}
}

void MeshRenderer::Bind()
{
	glBindVertexArray(VAO);
}

void MeshRenderer::Draw()
{
	mShader.Use();

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
	mShader.SetMat4("model", model);
	mShader.SetMat4("view", view);
	mShader.SetMat4("projection", projection);
	mShader.SetVec3("color", color.r, color.g, color.b);

	Bind();
	if (mMesh.IndicesSize() == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, mMesh.VerticesSize() / 3);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, mMesh.IndicesSize(), GL_UNSIGNED_INT, 0);
	}
}

void MeshRenderer::SetMesh(Mesh mesh)
{
	mMesh = mesh;
	Buffer();
}

void MeshRenderer::SetShader(const std::string& vertexPath, const std::string& fragPath)
{
	mShader = Shader{ vertexPath, fragPath };
}
