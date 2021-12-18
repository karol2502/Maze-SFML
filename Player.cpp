#include "Player.h"


Player::Player(int size, sf::Color color, int cellSize)
{
	dir = DIR::NONE;
	this->size = size;
	this->color = color;	

	this->setSize(sf::Vector2f(size, size));
	this->setFillColor(color);
	this->setOrigin(sf::Vector2f(size / 2.f, size / 2.f));
	this->setPosition(sf::Vector2f(cellSize / 2.f, cellSize / 2.f));
}

DIR Player::direction() const
{
	return dir;
}

void Player::updateDirection(DIR dir)
{
	this->dir = dir;
}
