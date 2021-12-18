#include <iostream>
#include "GameMenu.h"
#include "GameSettings.h"

GameMenu::GameMenu(sf::RenderWindow* window, GameStateManager* gameStateManager)
{
	this->window = window;
    this->gameStateManager = gameStateManager;
}

void GameMenu::Init()
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed font load!" << std::endl;
	}

	title = sf::Text("Maze", font, 160);	
	sf::Vector2u winSize = window->getSize();
	sf::FloatRect titleRect = title.getLocalBounds();

	title.setOrigin(sf::Vector2f(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f));
	title.setPosition(sf::Vector2f(winSize.x/2.f, 2.f * (winSize.y / 9.f )));
	
	buttons["start"] = new Button("Start", sf::Vector2f(winSize.x / 2.f, 5.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
	buttons["exit"] = new Button("Exit", sf::Vector2f(winSize.x / 2.f, 7.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
}

void GameMenu::Cleanup()
{
	for (auto const& elem : buttons)
	{
		delete elem.second;
	}
	buttons.clear();
}

void GameMenu::Pause()
{
}

void GameMenu::Resume()
{
}

void GameMenu::GetEvents()
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
					if (elem.first == "exit")
					{						
						window->close();
					}
					else if (elem.first == "start")
					{
						gameStateManager->ChangeState(new GameSettings(window, gameStateManager));
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

void GameMenu::Update()
{
}

void GameMenu::Display()
{
	window->clear(sf::Color::Black);
	window->draw(title);

	for (auto const& elem : buttons)
	{
		window->draw(*(elem.second));
	}

	window->display();
}