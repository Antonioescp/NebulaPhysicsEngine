#include "../include/application.h"

int main()
{
	Application app{ 800, 600, "Fireworks!" };
	app.RunLoop();
	return 0;
}
