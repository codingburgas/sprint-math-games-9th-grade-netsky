#pragma once

#include <utils.hpp>

class App
{
public:
	App(Vector2 setScreen, std::string setName);
	~App();


public:
	void Run();
	
private:
	GameState gameState;
	Vector2 screen; 
	std::string name;

};