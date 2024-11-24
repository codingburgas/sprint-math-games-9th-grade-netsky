#include <app.hpp>
#include <mainMenu.hpp>
#include <selectMenu.hpp>
#include <game1.hpp>
#include <game2.hpp>
#include <game3.hpp>
#include <ctime>

App::App(Vector2 setScreen, std::string setName)
	: screen(setScreen), name(setName), gameState(MENU)
{
	InitWindow((int)screen.x, (int)screen.y, name.c_str());
	SetTargetFPS(60);
	InitAudioDevice();   
	srand(unsigned int(time(0)));
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
		case GAME2:
			gameState = game2();
			break;
		case GAME3:
			gameState = game3();

			break;
		}
	}
}

