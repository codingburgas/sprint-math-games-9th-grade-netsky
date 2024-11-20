#include <app.hpp>

#include <mainMenu.hpp>
#include <selectMenu.hpp>

App::App(Vector2 setScreen, std::string setName)
	: screen(setScreen), name(setName), gameState(MENU)
{
	InitWindow((int)screen.x, (int)screen.y, name.c_str());
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
			gameState = selectMenu();
			break;
		}
	}
}
