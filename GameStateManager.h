#pragma once
#include <vector>
#include "GameState.h"

class GameStateManager
{
	std::vector<GameState*> states;

public:
	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();
	void Clear();
	GameState* GetCurrent();
};