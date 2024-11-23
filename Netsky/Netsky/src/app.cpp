#include <app.hpp>
#include <game1.hpp>
#include <mainMenu.hpp>
#include <selectMenu.hpp>
#include <ctime>

App::App(Vector2 setScreen, std::string setName)
	: screen(setScreen), name(setName), gameState(GAME1)
{
	InitWindow((int)screen.x, (int)screen.y, name.c_str());
	SetTargetFPS(60);
	InitAudioDevice();   
	srand(static_cast<unsigned int>(time(0)));
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
		case GAME1:
			gameState = game1(screen.x, screen.y);
			break;
		}
	}
}
