#include "GameSettings.h"
#include <iostream>
#include "GameLoading.h"

GameSettings::GameSettings(sf::RenderWindow* window, GameStateManager* gameStateManager)
{
	this->window = window;
	this->gameStateManager = gameStateManager;
}

void GameSettings::Init()
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed font load!" << std::endl;
	}

	title = sf::Text("Select the difficulty level", font, 120);
	sf::Vector2u winSize = window->getSize();
	sf::FloatRect titleRect = title.getLocalBounds();

	title.setOrigin(sf::Vector2f(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f));
	title.setPosition(sf::Vector2f(winSize.x / 2.f, 1.f * (winSize.y / 9.f)));

	buttons["easy"] = new Button("Easy", sf::Vector2f(winSize.x / 2.f, 3.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
	buttons["medium"] = new Button("Medium", sf::Vector2f(winSize.x / 2.f, 5.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
	buttons["hard"] = new Button("Hard", sf::Vector2f(winSize.x / 2.f, 7.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
}

void GameSettings::Cleanup()
{
	for (auto const& elem : buttons)
	{
		delete elem.second;
	}
	buttons.clear();
}

void GameSettings::Pause()
{
}

void GameSettings::Resume()
{
}

void GameSettings::GetEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::MouseButtonReleased)
		{
			for (auto const& elem : buttons)
			{
				if (elem.second->mouseHover(window))
				{
					if (elem.first == "easy")
					{
						gameStateManager->ChangeState(new GameLoading(10, 10, window, gameStateManager));
						return;
					}
					if (elem.first == "medium")
					{
						gameStateManager->ChangeState(new GameLoading(20, 20, window, gameStateManager));
						return;
					}
					if (elem.first == "hard")
					{
						gameStateManager->ChangeState(new GameLoading(30, 30, window, gameStateManager));
						return;
					}
				}
			}
		}			
	}	

	for (auto const& elem : buttons)
	{
		if (elem.second->mouseHover(window))
		{
			elem.second->setHover();
		}
		else
		{
			elem.second->setDefault();
		}
	}
}

void GameSettings::Update()
{
}

void GameSettings::Display()
{
	window->clear(sf::Color::Black);
	window->draw(title);

	for (auto const& elem : buttons)
	{
		window->draw(*(elem.second));		
	}

	window->display();
}
