#include "GamePause.h"
#include <iostream>
#include "GameMenu.h"

GamePause::GamePause(sf::RenderWindow* window, GameStateManager* gameStateManager)
{
	this->window = window;
	this->gameStateManager = gameStateManager;
}

void GamePause::Init()
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed font load!" << std::endl;
	}

	title = sf::Text("Pause", font, 160);
	sf::Vector2u winSize = window->getSize();
	sf::FloatRect titleRect = title.getLocalBounds();

	title.setOrigin(sf::Vector2f(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f));
	title.setPosition(sf::Vector2f(winSize.x / 2.f, 1.f * (winSize.y / 9.f)));

	buttons["resume"] = new Button("Resume", sf::Vector2f(winSize.x / 2.f, 3.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
	buttons["menu"] = new Button("Menu", sf::Vector2f(winSize.x / 2.f, 5.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
	buttons["exit"] = new Button("Exit", sf::Vector2f(winSize.x / 2.f, 7.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
}

void GamePause::Cleanup()
{
	for (auto const& elem : buttons)
	{
		delete elem.second;
	}
	buttons.clear();
}

void GamePause::Pause()
{
}

void GamePause::Resume()
{
}

void GamePause::GetEvents()
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
				gameStateManager->PopState();
				return;
			}
		}

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
					else if (elem.first == "resume")
					{
						gameStateManager->PopState();
						return;
					}
					else if (elem.first == "menu")
					{
						gameStateManager->ChangeState(new GameMenu(window, gameStateManager), 1);
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

void GamePause::Update()
{
}

void GamePause::Display()
{
	window->clear(sf::Color::Black);
	window->draw(title);

	for (auto const& elem : buttons)
	{
		window->draw(*(elem.second));
	}

	window->display();
}
