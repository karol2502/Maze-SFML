#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void GetEvents() = 0;
	virtual void Update() = 0;
	virtual void Display() = 0;
};