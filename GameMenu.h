#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Button.h"

class GameMenu :public GameState
{
	sf::RenderWindow* window;
	GameStateManager* gameStateManager;

	std::map<sf::String, Button*> buttons;

	sf::Font font;
	sf::Text title;

public:
	GameMenu(sf::RenderWindow* window, GameStateManager* gameStateManager);	

	void Init() override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

	void GetEvents() override;
	void Update() override;	
	void Display() override;
};