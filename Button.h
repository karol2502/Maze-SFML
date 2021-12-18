#pragma once
#include "SFML/Graphics.hpp"
#include<functional>
#include "GameStateManager.h"

class Button : public sf::Drawable
{
	sf::Color defaultColor = sf::Color(227, 227, 227, 255);
	sf::Color hoverColor = sf::Color(171, 171, 171, 255);
	sf::Color clickedColor = sf::Color(99, 99, 99, 255);

	sf::RectangleShape rectangle;
	sf::Text label;
	sf::Font font;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	Button(sf::String label, sf::Vector2f position, sf::Vector2f size, int fontSize);
	bool mouseHover(sf::RenderWindow* window) const;
	void setDefault();
	void setHover();		
};