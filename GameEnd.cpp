#include "GameEnd.h"
#include <iostream>
#include "GameMenu.h"

GameEnd::GameEnd(sf::RenderWindow* window, GameStateManager* gameStateManager, sf::Time time)
{
	this->window = window;
	this->gameStateManager = gameStateManager;
	this->time = time;
}

void GameEnd::Init()
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed font load!" << std::endl;
	}

	title = sf::Text("You found exit!", font, 120);
	sf::Vector2u winSize = window->getSize();

	sf::FloatRect titleRect = title.getLocalBounds();
	title.setOrigin(sf::Vector2f(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f));
	title.setPosition(sf::Vector2f(winSize.x / 2.f, 1.f * (winSize.y / 9.f)));

	std::string timeString = std::to_string(std::round(time.asSeconds() * 100.f) / 100.f);
	timeString.erase(timeString.find_last_not_of('0') + 1, std::string::npos);
	timeText = sf::Text("Your time:\n" + timeString + "s", font, 80);
	sf::FloatRect timeRect = timeText.getLocalBounds();
	timeText.setOrigin(sf::Vector2f(timeRect.left + timeRect.width / 2.0f, timeRect.top + timeRect.height / 2.0f));
	timeText.setPosition(sf::Vector2f(winSize.x / 2.f, 3.f * (winSize.y / 9.f)));

	buttons["menu"] = new Button("Menu", sf::Vector2f(winSize.x / 2.f, 6.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
	buttons["exit"] = new Button("Exit", sf::Vector2f(winSize.x / 2.f, 8.f * (winSize.y / 9.f)), sf::Vector2f(200.f, 100.f), 70);
}

void GameEnd::Cleanup()
{
	for (auto const& elem : buttons)
	{
		delete elem.second;
	}
	buttons.clear();
}

void GameEnd::Pause()
{
}

void GameEnd::Resume()
{
}

void GameEnd::GetEvents()
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
					else if (elem.first == "menu")
					{
						gameStateManager->ChangeState(new GameMenu(window, gameStateManager));
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

void GameEnd::Update()
{
}

void GameEnd::Display()
{
	window->clear(sf::Color::Black);
	window->draw(title);
	window->draw(timeText);

	for (auto const& elem : buttons)
	{
		window->draw(*(elem.second));
	}

	window->display();
}
