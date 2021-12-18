#include<iostream>
#include"Button.h"

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangle, states);
	target.draw(label, states);
}

Button::Button(sf::String label, sf::Vector2f position, sf::Vector2f size, int fontSize)
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed load font!" << std::endl;
	}
	this->label.setFont(font);
	this->label.setString(label);	
	this->label.setCharacterSize(fontSize);
	this->label.setFillColor(sf::Color::Black);

	rectangle = sf::RectangleShape(size);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(3.f);
	rectangle.setFillColor(sf::Color(227, 227, 227, 255));

	rectangle.setPosition(sf::Vector2f(position.x - size.x/2, position.y - size.y/2));
	
	sf::FloatRect labelRect = this->label.getLocalBounds();

	this->label.setOrigin(sf::Vector2f(labelRect.left + labelRect.width / 2.f, labelRect.top + labelRect.height / 2.f));
	this->label.setPosition(sf::Vector2f(position.x, position.y));
}

bool Button::mouseHover(sf::RenderWindow* window) const
{
	sf::FloatRect rectangleRect = rectangle.getGlobalBounds();
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));

	if (rectangleRect.contains(mousePosition))
	{
		return true;
	}
	return false;
}

void Button::setDefault()
{
	rectangle.setFillColor(defaultColor);
}

void Button::setHover()
{
	rectangle.setFillColor(hoverColor);
}
