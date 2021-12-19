#include "Player.h"


Player::Player(int size, sf::Color color, int cellSize)
{
	dir = sf::Vector2f(0.f, 0.f);
	this->size = size;
	this->color = color;

	this->setSize(sf::Vector2f(size, size));
	this->setFillColor(color);
	this->setPosition(sf::Vector2f(cellSize / 2.f - size / 2, cellSize / 2.f - size / 2));
}

sf::Vector2f Player::direction() const
{
	return dir;
}

void Player::updateDirection(float x, float y)
{
	this->dir = sf::Vector2f(x, y);
}
