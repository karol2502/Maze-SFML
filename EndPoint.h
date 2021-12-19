#pragma once
#include <SFML/Graphics.hpp>

class EndPoint : public sf::Drawable
{
	sf::RectangleShape rectangle;
	sf::Text label;
	sf::Font font;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	EndPoint(sf::String label, sf::Vector2f position, sf::Vector2f size, int fontSize);
	sf::FloatRect getGlobalBounds() const;
};

