#include <app.hpp>
#include <game1.hpp>
#include <mainMenu.hpp>
#include <selectMenu.hpp>
<<<<<<< HEAD
#include <game1.hpp>
#include <game2.hpp>
#include <game3.hpp>


=======
#include <ctime>
>>>>>>> 53fded120aa96afca4613c64f2d8d62c4857229e

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
<<<<<<< HEAD
			gameState = game1();
			break;
		case GAME2:
			gameState = game2();
			break;
		case GAME3:
			gameState = game3();
=======
			gameState = game1(screen.x, screen.y);
>>>>>>> 53fded120aa96afca4613c64f2d8d62c4857229e
			break;
		}
	}
}
