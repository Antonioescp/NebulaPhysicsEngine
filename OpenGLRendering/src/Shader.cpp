#include "Shader.h"


void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	unsigned int location = glGetUniformLocation(mID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::ID() const
{
	return mID;
}

Shader::Shader(const std::string vertexPath, const std::string fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexSourceFile;
	std::ifstream fragmentSourceFile;

	vertexSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentSourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexSourceFile.open(vertexPath.c_str());
		fragmentSourceFile.open(fragmentPath.c_str());

		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexSourceFile.rdbuf();
		fragmentStream << fragmentSourceFile.rdbuf();

		vertexSourceFile.close();
		fragmentSourceFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	LinkProgram(vertexShader, fragmentShader);
}

unsigned int Shader::CompileShader(GLenum type, const std::string& code) {
	unsigned int id;
	id = glCreateShader(type);

	const char* sourceCode = code.c_str();
	glShaderSource(id, 1, &sourceCode, nullptr);
	glCompileShader(id);

	int success;
	char* infoLog = nullptr;

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		infoLog = new char[length + 1];
		glGetShaderInfoLog(id, length, nullptr, infoLog);
		std::cerr << "SHADER::COMPILATION::VERTEX_SHADER_ERROR\n" << infoLog << std::endl;
		delete[] infoLog;
		id = 0;
	}

	return id;
}

void Shader::LinkProgram(const unsigned int vertexShader, const unsigned int fragmentShader) {
	mID = glCreateProgram();
	glAttachShader(mID, vertexShader);
	glAttachShader(mID, fragmentShader);
	glLinkProgram(mID);

	int success;
	char* infoLog = nullptr;

	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(mID, GL_LINK_STATUS, &length);
		infoLog = new char[length + 1];
		glGetProgramInfoLog(mID, length + 1, nullptr, infoLog);
		std::cerr << "PROGRAM::LINKING_ERROR\n" << infoLog << "\n";
		delete[] infoLog;
		mID = 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use() {
	glUseProgram(mID);
}

void Shader::SetBool(const std::string& name, bool value) const {
	unsigned int location = glGetUniformLocation(mID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetInt(const std::string& name, int value) const {
	unsigned int location = glGetUniformLocation(mID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value) const {
	unsigned int location = glGetUniformLocation(mID, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
	unsigned int location = glGetUniformLocation(mID, name.c_str());
	glUniform3f(location, x, y, z);
}