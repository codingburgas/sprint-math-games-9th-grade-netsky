#include <app.hpp>

int main()
{
	App* app = new App({ 1440, 800 }, "Netsky");
	app->Run();

	delete app;
}
