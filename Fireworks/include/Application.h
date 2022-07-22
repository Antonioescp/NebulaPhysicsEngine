#pragma once

#include <Window.h>
#include <Camera.h>
#include <Mesh.h>
#include <MeshRenderer.h>

#include "../include/Firework.h"

#include <random>
#include <vector>
#include <numbers>

#include <format>

import Core;

class Application : public Window
{
private:
	Mesh mCube;
	MeshRenderer mRenderer;
	Camera mMainCamera;
	std::vector<Firework::Rule> mFireworkRules{};
	std::vector<Firework> mFireworks{};
	std::vector<bool> mKeyPadPressed{};

	void HandleInput()
	{
		for (int i = 0; i < mFireworkRules.size(); i++)
		{
			if (glfwGetKey(mWindow, GLFW_KEY_KP_0 + i) == GLFW_PRESS && !mKeyPadPressed[i])
			{
				ShootFirework(mFireworkRules[i]);
				mKeyPadPressed[i] = true;
			}

			if (glfwGetKey(mWindow, GLFW_KEY_KP_0 + i) == GLFW_RELEASE)
			{
				mKeyPadPressed[i] = false;
			}
		}
	}

	void ShootFirework(Firework::Rule& rule)
	{
		// 100 particles on explosion and it will explode after 0.75s using common rule for children
		Firework newFirework{ rule };
		
		// Calculating a velocity around 45 and 120 degrees
		Nebula::real randomX = GetRandomRange(std::numbers::pi / 3.5f, std::numbers::pi / 1.5f);
		Nebula::Core::Vector3 startVelocity{ cos(randomX), 1.0f, 0.0f};
		startVelocity.Normalize();
		startVelocity *= 125.0f;

		newFirework.SetVelocity(startVelocity);
		newFirework.SetPosition(0.0f, 1.0f, 0.0f);
		newFirework.SetAcceleration(Nebula::Core::Vector3::Gravity * 10.0f);
		newFirework.SetMass(1.0f);
		newFirework.SetDamping(0.99f);

		mFireworks.push_back(newFirework);
	}

	void CreateFireworkTypes()
	{
		// Very fast explosion with a lot of particles
		mFireworkRules.emplace_back(
			Firework::Rule{
				100, // payloadCount
				0.75f, // minimum fuse time
				1.00f, // maximum fuse time
				100.0f, // minimum speed
				150.0f, // maximum speed
				0.50f, // minimum damping
				0.99f, // maximum damping
				{ 1.0f, 0.0f, 0.0f },
				Firework::Rule{ // Children rule
					0,
					1.0f,
					1.5f,
					100.0f,
					150.0f,
					0.01f,
					0.60f,
					{ 1.0f, 1.0f, 0.0f },
					{}
				}
			}
		);

		// Slow explosion with low particles
		mFireworkRules.emplace_back(
			Firework::Rule{
				50,
				0.75f, 1.0f,
				0.0f, 0.0f,
				0.99f,
				0.99f,
				{ 1.0f, 0.0f, 1.0f },
				Firework::Rule {
					25,
					0.25f, 0.50f,
					50.0f, 100.0f,
					0.01f, 0.60f,
					{ 1.0f, 0.5f, 0.5f },
					Firework::Rule {
						0,
						0.50f, 0.75f,
						50.0f, 100.0f,
						0.01f, 0.60f,
						{ 1.0f, 1.0f, 0.5f },
						{}
					}
				}
			}
		);

		// Fast Explosion With fast child explosion
		mFireworkRules.emplace_back(
			Firework::Rule{
				25,
				1.00f, 1.25f,
				0.00f, 0.00f,
				0.99f, 0.99f,
				{ 1.0f, 0.0f, 0.0f },
				Firework::Rule {
					5,
					0.25f, 0.50f,
					25.0f, 50.0f,
					0.05f, 0.10f,
					{ 0.0f, 1.0f, 0.0f },
					Firework::Rule {
						0,
						2.00f, 2.00f,
						05.0f, 15.0f,
						0.01f, 0.10f,
						{ 0.0f, 0.0f, 1.0f },
						{}
					}
				}
			}
		);

		// Continous Explosion
		mFireworkRules.emplace_back(
			Firework::Rule {
				2,
				0.75f, 1.00f,
				0.0f, 0.0f,
				0.99f, 0.99f,
				{ 1.0f, 0.0f, 0.0f },
				Firework::Rule {
					4,
					0.10f, 0.15f,
					5.0f, 20.0f,
					0.05f, 0.10f,
					{ 1.0f, 1.0f, 0.0f },
					Firework::Rule {
						4,
						0.10f, 0.15f,
						5.0f, 20.0f,
						0.05f, 0.10f,
						{ 0.0f, 1.0f, 1.0f },
						Firework::Rule {
							4,
							1.0f, 2.0f,
							5.0f, 20.0f,
							0.01f, 0.05f,
							{ 0.0f, 0.0f, 1.0f },
							{}
						}
					}
				}
			}
		);
	}

public:
	Application(int width, int height, std::string_view title)
		: Window(width, height, title)
		, mCube{}
		, mRenderer{
				mCube,
				SHADER_DIR R"(common.vert)",
				SHADER_DIR R"(common.frag)",
			}
		, mMainCamera{}
	{}

protected:
	void Setup() override
	{
		CreateFireworkTypes();

		mKeyPadPressed.resize(10, false);

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
		mRenderer.position = { 0.0f, 0.0f, 0.0f };

		mMainCamera.position = { 0.0f, 45.0f, 100.0f };
		mRenderer.view = mMainCamera.GetViewMatrix();
		mRenderer.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 100.0f);
		mRenderer.scale = { 1.0f, 1.0f, 1.0f };
	}
	
	void Update() override
	{
		HandleInput();

		std::vector<Firework> children{};

		for (auto& firework : mFireworks)
		{
			firework.Update(GetDeltaTime());
			if (firework.ShouldExplode() && !firework.HasExploded())
			{
				auto newFireworks = firework.Explode();
				children.insert(children.end(), newFireworks.begin(), newFireworks.end());
			}
		}

		mFireworks.insert(mFireworks.end(), children.begin(), children.end());
		std::erase_if(mFireworks, [](const Firework& element) -> bool { return element.HasExploded(); });
	}

	void Draw() override
	{
		for (auto& firework : mFireworks)
		{
			mRenderer.position = firework.GetPosition();

			mRenderer.color = {
				GetRandomRange(0.0f, 1.0f),
				GetRandomRange(0.0f, 1.0f),
				GetRandomRange(0.0f, 1.0f)
			};

			Nebula::real currentScale{ firework.GetAge() / firework.GetBaseAge() };
			mRenderer.scale = Nebula::Core::Vector3{ 1.0f, 1.0f, 1.0f } * currentScale;
			mRenderer.Draw();
		}
	}
};
