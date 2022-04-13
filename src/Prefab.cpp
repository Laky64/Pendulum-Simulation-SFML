#include <iostream>
#include "../include/Prefab.h"

Prefab::Prefab()
{
	circle.setRadius(20);
	circle.setFillColor(sf::Color(120, 120, 120, 255));
	this->connectionTofixPoint[0].color = sf::Color(150, 150, 150, 200);
	this->connectionTofixPoint[1].color = sf::Color(150, 150, 150, 200);

	this->connectionTofixPoint[0].position = sf::Vector2f(720, 0);
}

void Prefab::setPos(float xPos)
{
	std::cout << xPos << "\n";
	this->xPos = xPos * this->lenght;
	float width = this->lenght;
	this->yPos = sin(acos(this->xPos * (1 / width) - 1)) * width;
	circle.setPosition(this->xPos + 700 - lenght, this->yPos);
	this->connectionTofixPoint[1].position = sf::Vector2f(this->xPos + 720 - lenght, this->yPos + 20);
}

void Prefab::setLenght(float lenght)
{
	this->lenght = lenght;
	float alpha = atan(float(circle.getPosition().y) / (700 - float(circle.getPosition().x)));
	circle.setPosition(700 + (cos(abs(alpha)) * -this->lenght * (alpha / abs(alpha))), (sin(abs(alpha)) * this->lenght));
	this->connectionTofixPoint[1].position = sf::Vector2f(720 + (cos(abs(alpha)) * -this->lenght * (alpha / abs(alpha))), (sin(abs(alpha)) * this->lenght) + 20);
}

float Prefab::getLenght()
{
	return this->lenght;
}

sf::Vector2f Prefab::getPos()
{
	return this->circle.getPosition();
}

void Prefab::render(sf::RenderWindow *window)
{
	window->draw(connectionTofixPoint, 2, sf::Lines);
	window->draw(this->circle);
}
