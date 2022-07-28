#include "Application.h"

Application* gApplication{ nullptr };

Application::Application(int width, int height, std::string_view title)
	: Window(width, height, title)
{}

void Application::UpdateProjection(int width, int height)
{
	mProjection = glm::perspective(
		glm::radians(45.0f),
		static_cast<float>(width) / height,
		0.01f,
		100.0f
	);
}

void Application::HandleInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}
}

void Application::Setup()
{
	int width, height;
	glfwGetWindowSize(mWindow, &width, &height);
	glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallback);

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

	UpdateProjection(width, height);

	mRenderer.SetMesh(mCube);
	mRenderer.color = { 1.0f, 1.0f, 1.0f };
	mRenderer.projection = mProjection;

	mCamera.position = { 0.0f, 0.0f, 50.0f };
	mRenderer.view = mCamera.GetViewMatrix();
}

void Application::Update()
{
	mRegistry.UpdateForces(GetDeltaTime());

	for (auto& [particle, _] : mDrawableParticles)
	{
		particle->Integrate(GetDeltaTime());
	}
}

void Application::Draw()
{
	mRenderer.projection = mProjection;

	for (const auto& [particle, color] : mDrawableParticles)
	{
		mRenderer.scale = mParticleScale;
		mRenderer.position = particle->GetPosition();
		mRenderer.color = color;
		mRenderer.Draw();
	}
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	gApplication->UpdateProjection(width, height);
}