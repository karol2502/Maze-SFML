#include "Game.h"
#include<iostream>

void Game::Init()
{	
	running = true;

	window = new sf::RenderWindow();
	window->create(sf::VideoMode(1280, 720, 32), "Maze SFML", sf::Style::Titlebar | sf::Style::Close);

	gameStateManager = new GameStateManager();	
	gameStateManager->ChangeState(new GameMenu(window, gameStateManager));
}

void Game::Run()
{
	while (window->isOpen())
	{
		GameState* currentState = gameStateManager->GetCurrent();
		if (currentState == nullptr)
		{
			window->close();
			break;
		}
		currentState->GetEvents();		
		if (currentState == gameStateManager->GetCurrent())
		{
			currentState->Update();			
		}
		if (currentState == gameStateManager->GetCurrent())
		{			
			currentState->Display();
		}
	}

	Game::Clear();
}

void Game::Clear()
{
	GameState* currentState = gameStateManager->GetCurrent();
	if (currentState != NULL)
	{		
		gameStateManager->Clear();
	}	

	delete gameStateManager;	
	delete window;
}
