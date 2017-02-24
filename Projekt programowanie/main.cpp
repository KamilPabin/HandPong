#include "App.h"
#include <cstdlib>
#include <ctime>
int main()
{
	srand(time(NULL));
	App app(640, 480);
	app.Run();
}