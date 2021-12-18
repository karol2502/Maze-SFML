#include "GameLoading.h"
#include <iostream>
#include "GamePlay.h"

GameLoading::GameLoading(int width, int height, sf::RenderWindow* window, GameStateManager* gameStateManager)
{
	this->window = window;
	this->gameStateManager = gameStateManager;
	this->width = width;
	this->height = height;
}

void GameLoading::Init()
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed font load!" << std::endl;
	}

	title = sf::Text("Loading...", font, 160);
	sf::Vector2u winSize = window->getSize();
	sf::FloatRect titleRect = title.getLocalBounds();

	title.setOrigin(sf::Vector2f(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f));
	title.setPosition(sf::Vector2f(winSize.x / 2.f, winSize.y / 2.f));
}

void GameLoading::Cleanup()
{	
}

void GameLoading::Pause()
{
}

void GameLoading::Resume()
{
}

void GameLoading::GetEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void GameLoading::Update()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asMilliseconds() >= 500)
	{
		gameStateManager->ChangeState(new GamePlay(width, height, window, gameStateManager));
		return;
	}
}

void GameLoading::Display()
{
	window->clear(sf::Color::Black);
	window->draw(title);
	window->display();
}
