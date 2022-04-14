#include "Graph.h"

Graph::Graph(sf::RenderWindow* window, float startPosition, float endPosition, float startPositionY, float height, float maxValue, sf::Color color)
{

	this->Background = new GUI::Rect(GUI::Style::Normal({
    "sizeX:" + std::to_string(endPosition - startPosition),
    "sizeY:"  + std::to_string(height),
    "PositionX:" + std::to_string(startPosition),
    "PositionY:" + std::to_string(startPositionY),
    "Color: (39,39,39,255)", 
    "OutlineThickness: 2",
    "OutlineColor: (200,200,200,200)"
		}));
    this->clear(window);
    this->color = "Color: (" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")";
    this->GraphCircle = new GUI::Circle(GUI::Style::Normal({
    "radius: 2",
    "PositionX:" + std::to_string(startPosition),
    "PositionY:" + std::to_string(startPositionY + height),
    "OutlineColor: (200,200,200,200)",
    "OutlineThickness: 0",
    this->color
        }));

    this->maxValue = maxValue;
    this->height = height;
    this->xPos = startPosition;
    this->startPosition = startPosition;
    this->endPosition = endPosition;
    this->positionY = startPositionY + height;
}

Graph::~Graph()
{
}

void Graph::update(float value)
{
    this->GraphCircle->setPosition(this->xPos + 0.7, this->positionY - 3 - (value / maxValue) * height);
    this->xPos += 0.7;
}

void Graph::setPositions(float startPosition, float endPosition, float startPositionY, float height, float maxValue)
{
    this->Background = new GUI::Rect(GUI::Style::Normal({
    "sizeX:" + std::to_string(endPosition - startPosition),
    "sizeY:" + std::to_string(height),
    "PositionX:" + std::to_string(startPosition),
    "PositionY:" + std::to_string(startPositionY),
    "Color: (39,39,39,255)",
    "OutlineThickness: 2",
    "OutlineColor: (200,200,200,200)"
        }));

    this->GraphCircle = new GUI::Circle(GUI::Style::Normal({
    "radius: 2",
    "PositionX:" + std::to_string(startPosition),
    "PositionY:" + std::to_string(startPositionY + height),
    "OutlineColor: (200,200,200,200)",
    "OutlineThickness: 0",
    this->color
        }));
    std::cout << this->color << "\n";
    this->maxValue = maxValue;
    this->height = height;
    this->xPos = startPosition;
    this->startPosition = startPosition;
    this->endPosition = endPosition;
    this->positionY = startPositionY + height;
}

void Graph::render(sf::RenderWindow* window)
{
    this->GraphCircle->render(window);
    if (this->xPos >= this->endPosition) {
        
        clear(window);
        this->xPos = this->startPosition;
    }
}

void Graph::clear(sf::RenderWindow* window)
{
    this->Background->render(window);
}


