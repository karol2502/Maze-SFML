#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateManager.h"
#include "GameMenu.h"

class Game
{
	sf::RenderWindow* window;

	GameStateManager* gameStateManager;
	bool running;

	void Clear();

public:	
	void Init();
	void Run();		
};