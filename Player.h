#pragma once
#include <SFML/Graphics.hpp>

enum class DIR { UP, RIGHT, DOWN, LEFT, NONE };

class Player: public sf::RectangleShape
{
	int size;	
	sf::Color color;
	sf::Vector2f position;
		
	DIR dir;

public:
	Player(int size, sf::Color color, int cellSize);

	DIR direction() const;
	void updateDirection(DIR dir);

};

