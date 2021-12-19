#include "EndPoint.h"
#include <iostream>

void EndPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangle, states);
	target.draw(label, states);
}

EndPoint::EndPoint(sf::String label, sf::Vector2f position, sf::Vector2f size, int fontSize)
{
	if (!font.loadFromFile("./Assets/Fonts/landsand.otf"))
	{
		std::cout << "Failed load font!" << std::endl;
	}
	this->label.setFont(font);
	this->label.setString(label);
	this->label.setCharacterSize(fontSize);
	this->label.setFillColor(sf::Color(201, 201, 201));

	rectangle = sf::RectangleShape(size);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(1.5f);
	rectangle.setFillColor(sf::Color(25, 125, 52, 255));

	rectangle.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));

	sf::FloatRect labelRect = this->label.getLocalBounds();

	this->label.setOrigin(sf::Vector2f(labelRect.left + labelRect.width / 2.f, labelRect.top + labelRect.height / 2.f));
	this->label.setPosition(sf::Vector2f(position.x, position.y));
}

sf::FloatRect EndPoint::getGlobalBounds() const
{
	return rectangle.getGlobalBounds();
}
