#pragma once
#include "GameState.h"
#include "MazeGenerator.h"
#include <iostream>
#include "GameStateManager.h"
#include "Player.h"
#include "EndPoint.h"

class GamePlay :public GameState
{
	int width;
	int height;

	sf::Vector2f vertWallSize = sf::Vector2f(50, 100);
	sf::Vector2f horWallSize = sf::Vector2f(100, 50);

	int borderSize = 6;
	int cellSize = 100;

	sf::Color bgColor = sf::Color::Black;
	sf::Color wallsColor = sf::Color(138, 25, 36);

	sf::View viewPlay;
	sf::View defaultView;

	MazeGenerator mazeGenerator;
	std::map<int, int> maze;

	sf::RenderWindow* window;
	GameStateManager* gameStateManager;

	std::vector<sf::RectangleShape*> walls;
	std::vector<sf::RectangleShape*> visibleWalls;

	sf::Clock clock;
	sf::Time playTime;

	Player player;
	float playerSpeed = 300.f;

	EndPoint endPoint;

	void DrawMaze();
	void CalculateVisibleWalls();

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

