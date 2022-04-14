#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include "GUI.h"

class Graph
{
private:
	float xPos;
	float startPosition;
	float height;
	float endPosition;
	float maxValue;
	float positionY;
	GUI::Rect* Background;
	GUI::Circle* GraphCircle;
	std::string color;
public:
	Graph(sf::RenderWindow* window, float startPosition, float endPosition, float startPositionY, float height, float maxValue, sf::Color color);
	virtual ~Graph();
	void render(sf::RenderWindow* window);
	void clear(sf::RenderWindow* window);
	void update(float value);
	void setPositions(float startPosition, float endPosition, float startPositionY, float height, float maxValue);
};

