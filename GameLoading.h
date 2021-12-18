#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "GamePlay.h"

class GameLoading :public GameState
{
	sf::RenderWindow* window;
	GameStateManager* gameStateManager;

	sf::Font font;
	sf::Text title;
	sf::Clock clock;

	int width;
	int height;

public:
	GameLoading(int width, int height, sf::RenderWindow* window, GameStateManager* gameStateManager);

	void Init() override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

	void GetEvents() override;
	void Update() override;
	void Display() override;
};