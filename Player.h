#pragma once
#include <SFML/Graphics.hpp>

class Player: public sf::RectangleShape
{
	int size;	
	sf::Color color;
	sf::Vector2f position;
		
	sf::Vector2f dir;

public:
	Player(int size, sf::Color color, int cellSize);

	sf::Vector2f direction() const;
	void updateDirection(float x, float y);
};

