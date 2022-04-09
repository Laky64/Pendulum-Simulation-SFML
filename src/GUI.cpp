#include <iostream>
#include "../include/GUI.h"
#include "../include/Game.h"

// Style

std::map<std::string, float> GUI::Style::Button(std::initializer_list<std::string> list)
{
	// creates a Dictionary wirh all defiened style properties
	std::map<std::string, float> a;
	for (auto elem : list)
	{
		if (elem.find("Color") != 18446744073709551615)
		{
			a[elem.substr(0, elem.find(":")) + "R"] = std::stof(elem.substr(elem.find("(") + 1, elem.find(",") - elem.find("(") - 1));
			a[elem.substr(0, elem.find(":")) + "G"] = std::stof(elem.substr(elem.find(",") + 1, elem.find(",", elem.find(",") + 1) - elem.find(",") - 1));
			a[elem.substr(0, elem.find(":")) + "B"] = std::stof(elem.substr(elem.find(",", elem.find(",") + 1) + 1, elem.find(")") - elem.find(",", elem.find(",") + 1) - 1));
		}
		else
		{
			a[elem.substr(0, elem.find(":"))] = std::stof(elem.substr(elem.find(":") + 1, -1));
		}
	}
	return a;
}

void GUI::Button::render(sf::RenderWindow *window)
{
	// Button

	window->draw(this->ButtonObject);
	// Text

	// Style

	this->MousePos = sf::Mouse::getPosition(*window);
}

// Constructor + Destructor
GUI::Button::Button()
{
}

GUI::Button::~Button()
{
}

void GUI::Button::update()
{

	std::cout << style["OutlineThickness"] << "\n";
	if (this->MousePos.x > style["PositionX"] - style["OutlineThickness"] && this->MousePos.x < style["PositionX"] + style["sizeX"] + style["OutlineThickness"] && this->MousePos.y > style["PositionY"] - style["OutlineThickness"] && this->MousePos.y < style["PositionY"] + style["sizeY"] + style["OutlineThickness"])
	{
		this->changeStyle(this->HoverStyle);
	}
	else
	{
		this->changeStyle(this->style);
	}
}

bool GUI::Button::getState()
{
	return false;
}

void GUI::Button::changeStyle(std::map<std::string, float> a)
{
	this->ButtonObject.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"]));
	this->ButtonObject.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->ButtonObject.setPosition(a["PositionX"], a["PositionY"]);
	this->ButtonObject.setOutlineThickness(a["OutlineThickness"]);
	this->ButtonObject.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"]));
}

void GUI::Button::setStyle(std::map<std::string, float> a)
{
	this->style = a;
	this->HoverStyle = a;
	this->changeStyle(a);
}

void GUI::Button::setHoverStyle(std::map<std::string, float> a)
{
	this->HoverStyle = this->style;
	std::swap(this->HoverStyle, a);
	this->HoverStyle.insert(a.begin(), a.end());
}

void GUI::Slider::render()
{
}

// Constructor + Destructor
GUI::Slider::Slider()
{
}

GUI::Slider::~Slider()
{
}

void GUI::Slider::update()
{
}

float GUI::Slider::getValue()
{
	return 0.0f;
}
