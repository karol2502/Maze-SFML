#include "GameStateManager.h"

void GameStateManager::ChangeState(GameState* state)
{
	// Cleanup the current state.
	if (!states.empty())
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();
	}

	// Store and init the new state.
	states.push_back(state);
	states.back()->Init();
}

// Pause the current state and go to a new state.
void GameStateManager::PushState(GameState* state)
{
	if (!states.empty())
		states.back()->Pause();

	states.push_back(state);
	states.back()->Init();
}

// Leave current state and go to previous state.
void GameStateManager::PopState()
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();
	}

	if (!states.empty())
		states.back()->Resume();
}

void GameStateManager::Clear()
{
	while (!states.empty())
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();		
	}
}

GameState* GameStateManager::GetCurrent()
{
	if (!states.empty())
	{
		return states.back();
	}
	else
	{
		return nullptr;
	}	
}
