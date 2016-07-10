#include "Player.h"

Player::Player() : points(0)
{
}

Player::Player(string name, int points) : name(name), points(points)
{
}

void Player::setName(string nombre)
{
	this->name = nombre;
}

void Player::setPoints(int puntaje)
{
	this->points = puntaje;
}

string Player::getName() const
{
	return name;
}

int Player::getPoints() const
{
	return points;
}
