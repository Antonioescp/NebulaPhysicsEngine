#pragma once

#include <Window.h>
#include <Mesh.h>
#include <MeshRenderer.h>
#include <Camera.h>

#include <Particle.h>
#include <ParticleForceRegistry.h>

#include <vector>
#include <GLFW/glfw3.h>

class Application : public Window 
{
protected:

	Mesh mCube{};
	MeshRenderer mRenderer{ mCube, SHADER_DIR "common.vert", SHADER_DIR "common.frag" };
	Camera mCamera{};
	glm::mat4 mProjection{1.0f};

	std::vector<std::pair<Nebula::Particle*, glm::vec3>> mDrawableParticles{};
	Nebula::Vector3 mParticleScale{ 1.0f, 1.0f, 1.0f };

	Nebula::ForceGenerators::ParticleForceRegistry mRegistry{};

	Nebula::Vector3 mBackgroundColor{};

public:

	Application(int width, int height, std::string_view title);

	void UpdateProjection(int width, int height);
	virtual void HandleInput() override;
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Draw() override;
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Application* GetApplication();