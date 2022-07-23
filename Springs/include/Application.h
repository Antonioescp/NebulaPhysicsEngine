#pragma once

#include <Window.h>
#include <Mesh.h>
#include <MeshRenderer.h>
#include <Camera.h>
#include <ParticleForceRegistry.h>
#include <ParticleSpring.h>
#include <ParticleAnchoredSpring.h>
#include <ParticleGravity.h>
#include <ParticleBungee.h>
#include <ParticleBuoyancy.h>

#include <vector>

import Core;

using namespace Nebula;
using namespace Nebula::Core;

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
	std::vector< std::pair<Particle*, IParticleForceGenerator*> > mParticleLinks{};
	std::vector< std::pair<Particle*, glm::vec3> > mDrawableParticles{};

	ParticleGravity mEarthGravity{ {0.0f, -9.81f, 0.0f} };

	// Common spring
	Particle mCommonSpringStart{};
	Particle mCommonSpringEnd{};
	ParticleSpring mCommonSpring{ mCommonSpringStart, 100.0f, 9.0f };
	
	// Anchored spring
	Vector3 mAnchor{ -30.0f, 10.0f, 0.0f };
	Particle mAnchoredParticle{};
	ParticleAnchoredSpring mAnchoredSpring{ mAnchor, 100.0f, 9.0f };

	// Bungee spring
	Particle mAnchorBungeeParticle{};
	Particle mBungeeParticle{};
	ParticleBungee mBungeeSpring{ mAnchorBungeeParticle, 100.0f, 20.0f };

	// Buoyant particle
	Particle mBuoyantParticle{};
	ParticleBuoyancy mBuoyancyForce{ -10.0f, 0.1f, 0.0f, 500.0f };

	void CreateParticles()
	{
		// common spring
		mCommonSpringStart.SetMass(1.0f);
		mCommonSpringStart.SetDamping(0.99f);
		mCommonSpringStart.SetPosition(-40.0f, 10.0f, 0.0f);

		mCommonSpringEnd.SetMass(1.0f);
		mCommonSpringEnd.SetDamping(0.99f);
		mCommonSpringEnd.SetPosition(-40.0f, 0.0f, 0.0f);

		mDrawableParticles.push_back({ &mCommonSpringStart, { 1.0f, 0.64f, 0.0f } });
		mDrawableParticles.push_back({ &mCommonSpringEnd, {1.0f, 1.0f, 1.0f} });

		mParticleLinks.push_back({ &mCommonSpringEnd, &mCommonSpring });

		// Anchored spring
		mAnchoredParticle.SetMass(1.0f);
		mAnchoredParticle.SetDamping(0.99f);
		mAnchoredParticle.SetPosition(-30.0f, 0.0f, 0.0f);

		mDrawableParticles.push_back({ &mAnchoredParticle, {1.0f, 1.0f, 1.0f} });
		mParticleLinks.push_back({ &mAnchoredParticle, &mAnchoredSpring });

		// Bungee spring
		mAnchorBungeeParticle.SetMass(1.0f);
		mAnchorBungeeParticle.SetDamping(0.99f);
		mAnchorBungeeParticle.SetPosition(-20.0f, 10.0f, 0.0f);

		mBungeeParticle.SetMass(1.0f);
		mBungeeParticle.SetDamping(0.99f);
		mBungeeParticle.SetPosition(-16.0f, 15.0f, 0.0f);

		mDrawableParticles.push_back({ &mAnchorBungeeParticle, { 1.0f, 0.63f, 0.0f } });
		mDrawableParticles.push_back({ &mBungeeParticle, {1.0f, 1.0f, 1.0f} });

		mParticleLinks.push_back({ &mBungeeParticle, &mBungeeSpring });
		mParticleLinks.push_back({ &mBungeeParticle, &mEarthGravity });

		// Buoyancy
		mBuoyantParticle.SetMass(1.0f);
		mBuoyantParticle.SetDamping(0.99f);
		mBuoyantParticle.SetPosition(0.0f, 10.0f, 0.0f);

		mDrawableParticles.push_back({ &mBuoyantParticle, {0.678f, 0.847f, 0.902f} });
		mParticleLinks.push_back({ &mBuoyantParticle, &mBuoyancyForce });
		mParticleLinks.push_back({ &mBuoyantParticle, &mEarthGravity });

		for (auto& [particle, forceGenerator] : mParticleLinks)
		{
			mRegistry.Add(*particle, *forceGenerator);
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
		mRenderer.scale = { 1.0f, 1.0f, 1.0f };
		mRenderer.color = { 1.0f, 1.0f, 1.0f };
		mRenderer.position = { 0.0f, 0.0f, 0.0f };
		mRenderer.projection = gProjection;

		mMainCamera.position = { 0.0f, 0.0f, 100.0f };
		mRenderer.view = mMainCamera.GetViewMatrix();
	}

	void HandleInput() override
	{

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
			mRenderer.position = particle->GetPosition();
			mRenderer.color = color;
			mRenderer.Draw();
		}
	}
};