#include <iostream>
#include "../include/GUI.h"
#include "../include/Game.h"

// Style

std::map<std::string, float> GUI::Style::Button(std::initializer_list<std::string> list)
{
	// creates a Dictionary with all defiened style properties
	std::map<std::string, float> a;
	for (auto elem : list)
	{
		if (elem.find("Color") != -1)
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

// Button

// Constructor + Destructor

GUI::Button::Button()
{
}

GUI::Button::~Button()
{
}

// Update + render
void GUI::Button::update(bool MouseButton)
{

	if (this->MousePos.x > style["PositionX"] - style["OutlineThickness"] && this->MousePos.x < style["PositionX"] + style["sizeX"] + style["OutlineThickness"] && this->MousePos.y > style["PositionY"] - style["OutlineThickness"] && this->MousePos.y < style["PositionY"] + style["sizeY"] + style["OutlineThickness"])
	{
		this->changeStyle(this->HoverStyle);
		if (MouseButton != leftMouseButton)
		{
			if (MouseButton)
			{
				leftMouseButton = MouseButton;
				return OnPressFuntion();
			}
			leftMouseButton = MouseButton;
		}
	}
	else
	{
		this->changeStyle(this->style);
	}
}

void GUI::Button::render(sf::RenderWindow *window)
{
	// Button
	window->draw(this->ButtonObject);

	// Text

	this->text.setFont(font);
	window->draw(this->text);

	this->MousePos = sf::Mouse::getPosition(*window);
}

// styleButton
void GUI::Button::changeStyle(std::map<std::string, float> a)
{
	this->ButtonObject.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], 255));
	this->ButtonObject.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->ButtonObject.setPosition(a["PositionX"], a["PositionY"]);
	this->ButtonObject.setOutlineThickness(a["OutlineThickness"]);
	this->ButtonObject.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], 255));
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

// set/get
bool GUI::Button::getState()
{
	return false;
}

void GUI::Button::setFunction(std::function<void()> a)
{
	OnPressFuntion = a;
}

// Text

void GUI::Button::setText(std::string text, sf::Font font, std::map<std::string, float> style)
{

	this->font = font;
	this->text.setPosition(this->style["PositionX"], this->style["PositionY"]);
	this->text.setString(text);
	this->text.setCharacterSize(style["Size"]);
	this->text.setFillColor(sf::Color(style["OutlineColorR"], style["OutlineColorG"], style["OutlineColorB"], 255));
}

// Slider

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
