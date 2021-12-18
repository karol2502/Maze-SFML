#include "GamePlay.h"
#include "GamePause.h"

void GamePlay::DrawMaze()
{
	for (int y = 0; y < 2 * height; y++)
	{
		//vertical walls
		if (y % 2 == 0)
		{
			for (int x = 0; x < width - 1; x++)
			{
				if (maze[y * (width - 1) + y / 2 + x] == 1)
				{
					sf::RectangleShape* wall = new sf::RectangleShape;
					wall->setSize(sf::Vector2f(vertWallSize.x, vertWallSize.y));
					wall->setFillColor(sf::Color::Red);
					wall->setPosition(sf::Vector2f(x * (cellSize + vertWallSize.x) + cellSize, y / 2 * (cellSize + horWallSize.y)));
					walls.emplace_back(wall);
				}
			}
		}
		//horizontal walls
		else
		{
			for (int x = 0; x < width; x++)
			{
				if (maze[y * (width - 1) + (int)(y / 2) + x] == 1)
				{
					sf::RectangleShape* wall = new sf::RectangleShape;
					wall->setSize(sf::Vector2f(horWallSize.x, horWallSize.y));
					wall->setFillColor(sf::Color::Red);
					wall->setPosition(sf::Vector2f(x * (vertWallSize.x + horWallSize.x), (int)(y / 2) * (cellSize + horWallSize.y) + cellSize));
					walls.emplace_back(wall);
				}
			}
		}

		//corners
		for (int y = 0; y < height - 1; y++)
		{
			for (int x = 0; x < width - 1; x++)
			{
				sf::RectangleShape* corner = new sf::RectangleShape;
				corner->setSize(sf::Vector2f(vertWallSize.x, horWallSize.y));
				corner->setFillColor(sf::Color::Red);
				corner->setPosition(sf::Vector2f(x * (vertWallSize.x + horWallSize.x) + horWallSize.x, y * (cellSize + horWallSize.y) + cellSize));
				walls.emplace_back(corner);
			}
		}

		////borders
		//horizontal
		for (int i = 0; i < 2; i++)
		{
			sf::RectangleShape* wall = new sf::RectangleShape;
			wall->setSize(sf::Vector2f((width + 2*borderSize) * cellSize + (width - 1) * vertWallSize.x, borderSize * cellSize));
			wall->setPosition(sf::Vector2f(-borderSize * cellSize, -borderSize * cellSize + i * (height * cellSize + (height - 1) * horWallSize.y + borderSize * cellSize)));
			wall->setFillColor(sf::Color::Red);
			walls.emplace_back(wall);
		}
		//vertical
		for (int i = 0; i < 2; i++)
		{
			sf::RectangleShape* wall = new sf::RectangleShape;
			wall->setSize(sf::Vector2f(borderSize * cellSize, (width + 2*borderSize) * cellSize + (width - 1) * vertWallSize.x));
			wall->setPosition(sf::Vector2f(-borderSize * cellSize + i * (height * cellSize + (height - 1) * horWallSize.y + borderSize * cellSize), -borderSize * cellSize));
			wall->setFillColor(sf::Color::Red);
			walls.emplace_back(wall);
		}

	}
}

GamePlay::GamePlay(int width, int height, sf::RenderWindow* window, GameStateManager* gameStateManager)
	: mazeGenerator(width, height)
{
	this->width = width;
	this->height = height;

	this->window = window;
	this->gameStateManager = gameStateManager;

	vertWallSize = sf::Vector2f(50, 100);
	horWallSize = sf::Vector2f(100, 50);
	cellSize = 100;
	borderSize = 4;

	viewPlay.reset(sf::FloatRect(-500.f, -500.f, 3840.f, 2160.f));
	defaultView = window->getView();

	window->setView(viewPlay);

	mazeGenerator.Generate();
	maze = mazeGenerator.getGeneratedMaze();

	DrawMaze();		
}

void GamePlay::Init()
{
}

void GamePlay::Cleanup()
{	
	for (auto const& wall : walls)
	{
		delete wall;
	}	
	walls.clear();
}

void GamePlay::Pause()
{
	window->setView(defaultView);
}

void GamePlay::Resume()
{
	window->setView(viewPlay);
}

void GamePlay::GetEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				gameStateManager->PushState(new GamePause(window, gameStateManager));
				return;
			}
		}
	}
}

void GamePlay::Update()
{
}

void GamePlay::Display()
{
	window->clear(sf::Color::Black);

	for (auto const& value : walls)
	{
		window->draw(*value);
	}

	window->display();
}
