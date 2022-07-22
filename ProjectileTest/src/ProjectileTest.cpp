#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Mesh.h>
#include <MeshRenderer.h>
#include <Camera.h>

import Core;

enum class WeaponType
{
	Pistol,
	Artillery,
	Fireball,
	Laser
};

double deltaTime{};
float lastX;
float lastY;

bool firstMouse{ true };

Camera mainCamera{ {},{0.0f, 1.0f, 0.0f}, -155.0f, -25.0f };

WeaponType currentWeapon{ WeaponType::Pistol };
std::vector<Nebula::Core::Particle> projectiles;
std::vector<float> timers;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	float xoffset{ static_cast<float>(xpos - lastX) };
	float yoffset{ static_cast<float>(lastY - ypos) };
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	mainCamera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}

bool pressed = false;
bool weaponPressed = false;
void ProcessInput(GLFWwindow* window)
{
	const float cameraSpeed = static_cast<float>(5.0 * deltaTime); // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(Camera::Movement::Forward, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(Camera::Movement::Backward, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(Camera::Movement::Left, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(Camera::Movement::Right, cameraSpeed);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !pressed)
	{
		Nebula::Core::Particle p;
		p.SetPosition(0.0f, 2.0f, -5.0f);
		switch (currentWeapon)
		{
		case WeaponType::Pistol:
			p.SetMass(2.0f);
			p.SetVelocity(0.0f, 0.0f, -35.0f);
			p.SetAcceleration(0.0f, -1.0f, 0.0f);
			p.SetDamping(0.99f);
			break;

		case WeaponType::Artillery:
			p.SetMass(200.0f);
			p.SetVelocity(0.0f, 30.0f, -40.0f);
			p.SetAcceleration(0.0f, -20.0f, 0.0f);
			p.SetDamping(0.99f);
			break;

		case WeaponType::Fireball:
			p.SetMass(1.0f);
			p.SetVelocity(0.0f, 0.0f, -10.0f);
			p.SetAcceleration(0.0f, 0.6f, 0.0f);
			p.SetDamping(0.99f);
			break;

		case WeaponType::Laser:
			p.SetMass(0.1f);
			p.SetVelocity(0.0f, 0.0f, -100.0f);
			p.SetAcceleration(0.0f, 0.0f, 0.0f);
			p.SetDamping(0.99f);
			break;
		}

		projectiles.emplace_back(p);
		timers.emplace_back(0.0f);

		pressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		pressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && !weaponPressed)
	{
		currentWeapon = static_cast<WeaponType>((static_cast<int>(currentWeapon) + 1) % 4);
		weaponPressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
	{
		weaponPressed = false;
	}
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Demo", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	Mesh cube{};
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

	std::string_view commonVertexSource{ SHADER_DIR "common.vert" };
	std::string_view commonFragmentSource{ SHADER_DIR "common.frag" };

	MeshRenderer floor{ cube, std::string{commonVertexSource}, std::string{commonFragmentSource} };
	floor.position = { 0.0f, 0.0f, -5.0f };
	floor.scale = { 2.0f, 0.25f, 1.5f };
	floor.color = { 1.0f, 0.0f, 0.0f };

	MeshRenderer bullet{ cube, std::string{ commonVertexSource }, std::string{ commonFragmentSource } };
	bullet.position = { 0.0f, 2.5f, -5.0f };
	bullet.scale = { 0.25f, 0.25f, 0.25f };
	bullet.color = { 0.0f, 1.0f, 0.0f };

	mainCamera.position = { 25.0f, 17.0f, 0.0f };

	glfwSwapInterval(0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	double lastFrame{ glfwGetTime() };
	
	glEnable(GL_DEPTH_TEST);

	constexpr float TimeLimit = 5.0f;
	while (!glfwWindowShouldClose(window))
	{
		double currentFrame{ glfwGetTime() };
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.3f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ProcessInput(window);
		
		floor.view = mainCamera.GetViewMatrix();
		floor.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		for (int i = 0; i < 10; i++)
		{
			floor.position = { 0.0f, 0.0f, -5.0f * (i + 1) };
			floor.Draw();
		}

		bullet.view = mainCamera.GetViewMatrix();
		bullet.projection = floor.projection;

		for (auto& p : projectiles)
		{
			p.Integrate(static_cast<Nebula::real>(deltaTime));
			bullet.position = p.GetPosition();
			bullet.Draw();
		}

		std::vector<int> timersFinished;
		for (int i = 0; i < timers.size(); i++)
		{
			timers[i] += deltaTime;
			if (timers[i] >= TimeLimit)
			{
				timersFinished.emplace_back(i);
			}
		}

		for (int e : timersFinished)
		{
			auto projectilesIterator = projectiles.begin() + e;
			projectiles.erase(projectilesIterator);

			auto timersIterator = timers.begin() + e;
			timers.erase(timersIterator);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}