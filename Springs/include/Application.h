#pragma once

#include <vector>
#include <iostream>

#include <Window.h>
#include <Mesh.h>
#include <MeshRenderer.h>
#include <Camera.h>
#include <ParticleForceRegistry.h>
#include <ParticleSpring.h>
#include <ParticleGravity.h>
#include <ParticleDrag.h>

using namespace Nebula;
using namespace ForceGenerators;

glm::mat4 gProjection{ 1.0f };

void FramebufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	gProjection = glm::perspective(
		glm::radians(45.0f),
		static_cast<float>(width) / height,
		0.01f,
		100.0f
	);
}

class Application : public Window
{
private:

	Mesh mCube{};
	MeshRenderer mRenderer{ mCube, SHADER_DIR "common.vert", SHADER_DIR "common.frag" };
	Camera mMainCamera{};

	ParticleForceRegistry mRegistry{};
	std::vector< std::pair<Particle*, glm::vec3> > mDrawableParticles{};

	ParticleGravity mEarthGravity{ {0.0f, -0.1f, 0.0f} };
	Vector3 mParticleScale = { 1.0f, 1.0f, 1.0f };

	Particle mAnchorParticle{};
	std::vector<Particle> mRope{3};
	std::vector<ParticleSpring> mSprings{};

	void CreateParticles()
	{
		for (int i{}; i < mRope.size(); i++)
		{
			mDrawableParticles.push_back({ &mRope[i] , { 1.0f, 0.64f, 0.0f }});
			mRope[i].SetPosition(0.0f, 2.0f - 0.5f * i, 0.0f);

			if (i > 0) {
				mRegistry.Add(mRope[i], mEarthGravity);
			}

			if (i < mRope.size() - 1)
			{
				mSprings.push_back({ mRope[i], 1.0f, 1.0f });
			}
		}

		for (int i{ 0 }; i < mSprings.size(); i++)
		{
			mRegistry.Add(mRope[i + 1], mSprings[i]);
			if (i > 0) mRegistry.Add(mRope[i], mSprings[i - 1]);
		}
	}

public:

	Application(int width, int height, std::string_view title)
		: Window(width, height, title)
	{}

	void Setup() override
	{
		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);
		FramebufferCallback(mWindow, width, height);
		glfwSetFramebufferSizeCallback(mWindow, FramebufferCallback);
		glClearColor(192 / 255.0f, 57 / 255.0f, 43 / 255.0f, 1.0f);

		CreateParticles();

		mCube.AddVertices({
			 -0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		});

		mRenderer.SetMesh(mCube);
		mRenderer.color = { 1.0f, 1.0f, 1.0f };
		mParticleScale *= 0.25f;
		mRenderer.projection = gProjection;

		mMainCamera.position = { 0.0f, 0.0f, 10.0f };
		mRenderer.view = mMainCamera.GetViewMatrix();
	}

	void HandleInput() override
	{
		if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
		{
			mParticleScale += Vector3{ 1.0f, 1.0f, 1.0f } * GetDeltaTime();
		}

		if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
		{
			mParticleScale -= Vector3{ 1.0f, 1.0f, 1.0f } * GetDeltaTime();
		}
	}

	void Update() override
	{
		mRegistry.UpdateForces(GetDeltaTime());

		for (auto& [particle, _] : mDrawableParticles)
		{
			particle->Integrate(GetDeltaTime());
		}
	}

	void Draw() override
	{
		mRenderer.projection = gProjection;

		for (const auto& [particle, color] : mDrawableParticles)
		{
			mRenderer.scale = mParticleScale;
			mRenderer.position = particle->GetPosition();
			mRenderer.color = color;
			mRenderer.Draw();
		}
	}
};