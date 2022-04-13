#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Prefab
{
private:
	float xPos;
	float yPos;
	float lenght;
	sf::CircleShape circle;
	sf::Vertex connectionTofixPoint[2];
public:
	Prefab();
	void setPos(float xPos);
	void setLenght(float lenght);
	float getLenght();
	sf::Vector2f getPos();
	void render(sf::RenderWindow* window);
};

