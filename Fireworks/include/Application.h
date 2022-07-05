#pragma once

#include <Window.h>
#include <Camera.h>
#include <Mesh.h>
#include <MeshRenderer.h>

import Core;

class Application : public Window
{
private:
	Mesh cube;
	MeshRenderer renderer;
	Camera mainCamera;

public:
	Application(int width, int height, std::string_view title)
		: Window(width, height, title)
		, cube{}
		, renderer{
				cube,
				R"(E:\CodePlayground\C++\NebulaPhysicsEngine\Shaders\common.vert)",
				R"(E:\CodePlayground\C++\NebulaPhysicsEngine\Shaders\common.frag)"
			}
		, mainCamera{}
	{

	}

protected:
	void Setup()
	{
		cube.AddVertices({
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

		renderer.SetMesh(cube);
		renderer.color = { 1.0f, 1.0f, 1.0f };
		renderer.position = { 0.0f, -25.0f, 0.0f };

		mainCamera.Position = { 0.0f, 0.0f, 100.0f };
		renderer.view = mainCamera.GetViewMatrix();
		renderer.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 100.0f);
	}
	
	void Update()
	{

	}

	void Draw()
	{
		renderer.Draw();
	}
};
