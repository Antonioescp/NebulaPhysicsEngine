#include <Application.h>

int main()
{
	Application app{ 800, 600, "Springs!" };
	app.RunLoop();
	return 0;
}