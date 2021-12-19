#include "GameState.h"
#include "GameStateManager.h"
#include "Button.h"

class GameEnd :public GameState
{
	sf::RenderWindow* window;
	GameStateManager* gameStateManager;

	std::map<sf::String, Button*> buttons;

	sf::Font font;
	sf::Text title;
	sf::Text timeText;

	sf::Time time;

public:
	GameEnd(sf::RenderWindow* window, GameStateManager* gameStateManager, sf::Time time);

	void Init() override;
	void Cleanup() override;

	void Pause() override;
	void Resume() override;

	void GetEvents() override;
	void Update() override;
	void Display() override;
};
