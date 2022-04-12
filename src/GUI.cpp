#include <iostream>
#include "math.h"
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
	a["interpolation"] = 2;
	return a;
}

std::map<std::string, float> GUI::Style::Text(std::initializer_list<std::string> list)
{
	// creates a Dictionary with all defiened style properties
	std::map<std::string, float> a;
	for (auto elem : list)
	{

		if (elem.find("Style") != -1)
		{
			if (elem.find("Regular") != -1)
			{
				a[elem.substr(0, elem.find(":"))] *= 10;
				a[elem.substr(0, elem.find(":"))] += 1;
			}
			if (elem.find("Bold") != -1)
			{
				a[elem.substr(0, elem.find(":"))] *= 10;
				a[elem.substr(0, elem.find(":"))] += 2;
			}
			if (elem.find("Italic") != -1)
			{
				a[elem.substr(0, elem.find(":"))] *= 10;
				a[elem.substr(0, elem.find(":"))] += 3;
			}
			if (elem.find("Underlined") != -1)
			{
				a[elem.substr(0, elem.find(":"))] *= 10;
				a[elem.substr(0, elem.find(":"))] += 4;
			}
			if (elem.find("StrikeThrough") != -1)
			{
				a[elem.substr(0, elem.find(":"))] *= 10;
				a[elem.substr(0, elem.find(":"))] += 5;
			}
		}
		else if (elem.find("Position") != -1)
		{
			if (elem.find("Centered") != -1)
			{
				a[elem.substr(0, elem.find(":"))] = 1;
			}
			else if (elem.find("Left") != -1)
			{
				a[elem.substr(0, elem.find(":"))] = 2;
			}
			else if (elem.find("Right") != -1)
			{
				a[elem.substr(0, elem.find(":"))] = 3;
			}
			else
			{

				a[elem.substr(0, elem.find(":"))] = 1;
			}
		}
		else if (elem.find("Color") != -1)
		{
			a[elem.substr(0, elem.find(":")) + "R"] = std::stof(elem.substr(elem.find("(") + 1, elem.find(",") - elem.find("(") - 1));
			a[elem.substr(0, elem.find(":")) + "G"] = std::stof(elem.substr(elem.find(",") + 1, elem.find(",", elem.find(",") + 1) - elem.find(",") - 1));
			a[elem.substr(0, elem.find(":")) + "B"] = std::stof(elem.substr(elem.find(",", elem.find(",") + 1) + 1, elem.find(")") - elem.find(",", elem.find(",") + 1) - 1));
		}
		else
		{
			try
			{
				a[elem.substr(0, elem.find(":"))] = std::stof(elem.substr(elem.find(":") + 1, -1));
			}
			catch (const std::exception exc)
			{
				std::cout << "An Error occured while trying to implement Style: '" << elem << "' Error catched -> '" << exc.what() << "'"
						  << "\n";
			}
		}
	}
	a["interpolation"] = 2;
	return a;
}

// Button

// Constructor + Destructor

GUI::Button::Button()
{
	this->testLine[0].color = sf::Color(255, 0, 0, 255);
	this->testLine[1].color = sf::Color(255, 0, 0, 255);
}

GUI::Button::~Button()
{
}

// Update + render
bool GUI::Button::update(bool MouseButton)
{

	if (ceilf(this->currentStyle["interpolation"] * 10.0) / 10.0 != ceilf(this->activeStyle["interpolation"] * 10.0) / 10.0)
	{
		this->interpolateStyle();
	}
	if (this->MousePos.x > style["PositionX"] - style["OutlineThickness"] && this->MousePos.x < style["PositionX"] + style["sizeX"] + style["OutlineThickness"] && this->MousePos.y > style["PositionY"] - style["OutlineThickness"] && this->MousePos.y < style["PositionY"] + style["sizeY"] + style["OutlineThickness"])
	{
		if (MouseButton)
		{
			this->setActiveStyle(this->ClickedStyle);
		}
		else
		{
			this->setActiveStyle(this->HoverStyle);
		}
		if (MouseButton != leftMouseButton)
		{
			if (MouseButton)
			{
				leftMouseButton = MouseButton;
				return true;
			}
			leftMouseButton = MouseButton;
		}
	}
	else
	{
		this->setActiveStyle(this->style);
	}
	return false;
}

void GUI::Button::render(sf::RenderWindow *window)
{
	// Button
	window->draw(this->ButtonObject);

	// Text
	this->text.setFont(font);
	window->draw(this->text);

	// TestLine
	window->draw(this->testLine, 2, sf::Lines);

	// update MousePos
	this->MousePos = sf::Mouse::getPosition(*window);
}

// styleButton
void GUI::Button::changeStyle(std::map<std::string, float> a)
{
	this->currentStyle = a;
	this->ButtonObject.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], 255));
	this->ButtonObject.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->ButtonObject.setPosition(a["PositionX"], a["PositionY"]);
	this->ButtonObject.setOutlineThickness(a["OutlineThickness"]);
	this->ButtonObject.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], 255));
}

void GUI::Button::interpolateStyle()
{

	for (auto v1 : this->currentStyle)
	{
		for (auto v2 : this->activeStyle)
		{

			if (v1.first == v2.first && this->currentStyle[v1.first] != this->activeStyle[v1.first])
			{
				this->currentStyle[v1.first] += ((this->activeStyle[v1.first] - this->currentStyle[v1.first]) / this->interpolationDuration);
			}
		}
	}

	changeStyle(this->currentStyle);
}

void GUI::Button::setActiveStyle(std::map<std::string, float> a)
{
	if (lastActiveStyle != activeStyle)
	{
		this->currentStyle["interpolation"] = 1;
	}
	this->lastActiveStyle = this->activeStyle;
	this->activeStyle = a;
	this->activeStyle["interpolation"] = 2;
}

void GUI::Button::setStyle(std::map<std::string, float> a)
{
	this->style = a;
	this->currentStyle = a;
	this->activeStyle = a;
	this->lastActiveStyle = a;
	this->HoverStyle = a;
	this->changeStyle(a);
}

void GUI::Button::setClickedStyle(std::map<std::string, float> a)
{
	this->ClickedStyle = this->style;
	std::swap(this->ClickedStyle, a);
	this->ClickedStyle.insert(a.begin(), a.end());
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
// Text

void GUI::Button::setText(std::string text, sf::Font font, std::map<std::string, float> style)
{

	this->font = font;
	this->text.setFont(font);
	this->text.setLetterSpacing(style["LetterSpace"]);
	this->text.setString(text);
	sf::Uint32 styles = 0;

	if (std::to_string(style["Style"]).find("1") != -1)
	{
		styles += sf::Text::Regular;
	}
	if (std::to_string(style["Style"]).find("2") != -1)
	{
		styles += sf::Text::Bold;
	}
	if (std::to_string(style["Style"]).find("3") != -1)
	{
		styles += sf::Text::Italic;
	}
	if (std::to_string(style["Style"]).find("4") != -1)
	{
		styles += sf::Text::Underlined;
	}
	if (std::to_string(style["Style"]).find("5") != -1)
	{
		styles += sf::Text::StrikeThrough;
	}
	this->text.setStyle(styles);
	this->text.setCharacterSize(style["Size"]);
	this->text.setFillColor(sf::Color(style["ColorR"], style["ColorG"], style["ColorB"], 255));
	this->text.setOutlineColor(sf::Color(style["OutlineColorR"], style["OutlineColorG"], style["OutlineColorB"], 255));
	this->text.setOutlineThickness(style["OutlineThickness"]);
	float width = this->text.getLocalBounds().width;
	float height = this->text.getLocalBounds().height;

	switch (int(style["Position"]))
	{
	case (1):
		this->text.setPosition(int(this->style["PositionX"] + (this->style["sizeX"] - width) / 2 - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]), int(this->style["PositionY"] + (this->style["sizeY"] - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]));
		break;
	case (2):
		this->text.setPosition(int(this->style["PositionX"] - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]), int(this->style["PositionY"] + (this->style["sizeY"] - height) / 2 - (this->text.getCharacterSize() * 0.29)));
		break;
	case (3):
		this->text.setPosition(int(this->style["PositionX"] + this->style["sizeX"] - width - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]), int(this->style["PositionY"] + (this->style["sizeY"] - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]));
		break;
	default:
		this->text.setPosition(int(this->style["PositionX"] + (this->style["sizeX"] - width) / 2 - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]), int(this->style["PositionY"] + (this->style["sizeY"] - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]));
		break;
	}
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
