#include "GamePlay.h"
#include "GamePause.h"
#include "GameEnd.h"

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
					wall->setFillColor(wallsColor);
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
					wall->setFillColor(wallsColor);
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
				corner->setFillColor(wallsColor);
				corner->setPosition(sf::Vector2f(x * (vertWallSize.x + horWallSize.x) + horWallSize.x, y * (cellSize + horWallSize.y) + cellSize));
				walls.emplace_back(corner);
			}
		}

		////borders
		//horizontal
		for (int i = 0; i < 2; i++)
		{
			sf::RectangleShape* wall = new sf::RectangleShape;
			wall->setSize(sf::Vector2f((width + 2 * borderSize) * cellSize + (width - 1) * vertWallSize.x, borderSize * cellSize));
			wall->setPosition(sf::Vector2f(-borderSize * cellSize, -borderSize * cellSize + i * (height * cellSize + (height - 1) * horWallSize.y + borderSize * cellSize)));
			wall->setFillColor(wallsColor);
			walls.emplace_back(wall);
		}
		//vertical
		for (int i = 0; i < 2; i++)
		{
			sf::RectangleShape* wall = new sf::RectangleShape;
			wall->setSize(sf::Vector2f(borderSize * cellSize, (width + 2 * borderSize) * cellSize + (width - 1) * vertWallSize.x));
			wall->setPosition(sf::Vector2f(-borderSize * cellSize + i * (height * cellSize + (height - 1) * horWallSize.y + borderSize * cellSize), -borderSize * cellSize));
			wall->setFillColor(wallsColor);
			walls.emplace_back(wall);
		}

	}
}

void GamePlay::CalculateVisibleWalls()
{
	//clear vector every frame
	visibleWalls.clear();

	sf::Vector2f viewCenter(window->getView().getCenter());
	sf::Vector2f viewSize(window->getView().getSize());
	sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);

	for (auto const& value : walls)
	{
		if ((*value).getGlobalBounds().intersects(currentViewRect))
		{
			visibleWalls.emplace_back(value);
		}
	}
}

GamePlay::GamePlay(int width, int height, sf::RenderWindow* window, GameStateManager* gameStateManager)
	: mazeGenerator(width, height),
	player(40, sf::Color::Blue, 100),
	endPoint("Exit", sf::Vector2f((width - 1)* (cellSize + vertWallSize.x) + cellSize / 2.f, (height - 1)* (cellSize + horWallSize.y) + cellSize / 2.f), sf::Vector2f(60, 40), 40)
{
	this->width = width;
	this->height = height;

	this->window = window;
	this->gameStateManager = gameStateManager;

	viewPlay.reset(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
	viewPlay.setCenter(sf::Vector2f(cellSize / 2, cellSize / 2));
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

	// do poprawy
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.updateDirection(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.updateDirection(1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.updateDirection(0, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.updateDirection(0, 1);
	}
	else
	{
		player.updateDirection(0, 0);
	}
}

void GamePlay::Update()
{
	CalculateVisibleWalls();

	sf::Time elapsed = clock.getElapsedTime();
	playTime += elapsed;
	float delta = elapsed.asSeconds();
	clock.restart();

	float distance = playerSpeed * delta;
	sf::Vector2f futurePosition(player.getPosition() + player.direction() * distance);

	sf::FloatRect futureBounds(futurePosition, player.getSize());

	bool canMove = true;
	for (auto const& value : visibleWalls)
	{
		if (futureBounds.intersects(value->getGlobalBounds()))
		{
			canMove = false;
		}
	}
	if (canMove)
	{
		player.move(player.direction() * distance);
		viewPlay.move(player.direction() * distance);
		window->setView(viewPlay);
	}

	if (player.getGlobalBounds().intersects(endPoint.getGlobalBounds()))
	{
		gameStateManager->PushState(new GameEnd(window, gameStateManager, playTime));
		return;
	}
}

void GamePlay::Display()
{
	window->clear(bgColor);

	for (auto const& value : visibleWalls)
	{
		window->draw(*value);
	}
	window->draw(player);
	window->draw(endPoint);
	window->display();
}
