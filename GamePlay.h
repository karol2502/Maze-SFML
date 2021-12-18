#pragma once
#include "GameState.h"
#include "MazeGenerator.h"
#include <iostream>
#include "GameStateManager.h"

class GamePlay :public GameState
{
	int width;
	int height;

	sf::Vector2f vertWallSize;
	sf::Vector2f horWallSize;

	int borderSize;
	int cellSize;

	sf::View viewPlay;
	sf::View defaultView;

	MazeGenerator mazeGenerator;
	std::map<int, int> maze;

	sf::RenderWindow *window;
	GameStateManager *gameStateManager;

	std::vector<sf::RectangleShape*> walls;

	void DrawMaze();

public:		
	GamePlay(int width, int height, sf::RenderWindow* window, GameStateManager* gameStateManager);

	void Init() override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

	void GetEvents() override;
	void Update() override;
	void Display() override;
};

