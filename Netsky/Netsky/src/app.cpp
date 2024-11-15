#include <app.hpp>

#include <mainMenu.hpp>

App::App(Vector2 setScreen, std::string setName)
	: screen(setScreen), name(setName), gameState(MENU)
{
	InitWindow(800, 800, "Main menu");
	SetTargetFPS(60);
	InitAudioDevice();   
}
App::~App() {}

void App::Run()
{
	while (gameState != NIL)
	{
		switch (gameState)
		{
		case MENU:
			gameState = mainMenu();
			break;
		case GAME_SELECT:
			break;
		}
	}
}
