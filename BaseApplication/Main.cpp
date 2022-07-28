#include "Application.h"

int main()
{
	Application* app{ GetApplication() };
	app->RunLoop();
	delete app;
	return 0;
}