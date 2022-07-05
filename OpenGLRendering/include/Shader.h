#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	unsigned int mID;

	unsigned int CompileShader(GLenum type, const std::string& code);
	void LinkProgram(const unsigned int vertexShader, const unsigned int fragmentShader);

public:

	unsigned int ID() const;
	Shader(const std::string vertexPath, const std::string fragmentPath);
	void Use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetMat4(const std::string& name, const glm::mat4& value) const;
};