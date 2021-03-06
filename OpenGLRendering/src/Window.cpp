#include <Window.h>

Window::Window(int width, int height, std::string_view title)
	: mDeltaTime{}
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
	glfwMakeContextCurrent(mWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Window::RunLoop()
{
	Setup();

	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(0);
	
	float previousFrame = glfwGetTime();
	while (!glfwWindowShouldClose(mWindow))
	{
		float currentTime = glfwGetTime();
		mDeltaTime = currentTime - previousFrame;
		previousFrame = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		HandleInput();
		Update();
		Draw();

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

float Window::GetDeltaTime() const {
	return mDeltaTime;
}

void Window::HandleInput()
{
}

void Window::Setup()
{
}

void Window::Update()
{
}

void Window::Draw()
{
}