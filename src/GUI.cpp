#include <iostream>
#include "math.h"
#include "../include/GUI.h"
#include "../include/Game.h"
#include "../include/Prefab.h"

//------Style------//

std::map<std::string, float> GUI::Style::Normal(std::initializer_list<std::string> list)
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
			a[elem.substr(0, elem.find(":")) + "A"] = std::stof(elem.substr(elem.find(",", elem.find(",", elem.find(",") + 1) + 1) + 1, elem.find(")") - elem.find(",", elem.find(",", elem.find(",") + 1) + 1) - 1));
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
		else if (elem.find("PositionX") != -1)
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
		else if (elem.find("PositionY") != -1)
		{
			if (elem.find("Centered") != -1)
			{
				a[elem.substr(0, elem.find(":"))] = 1;
			}
			else if (elem.find("Top") != -1)
			{
				a[elem.substr(0, elem.find(":"))] = 2;
			}
			else if (elem.find("Bottom") != -1)
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
			a[elem.substr(0, elem.find(":")) + "A"] = std::stof(elem.substr(elem.find(",", elem.find(",", elem.find(",") + 1) + 1) + 1, elem.find(")") - elem.find(",", elem.find(",", elem.find(",") + 1) + 1) - 1));
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

//------Button------//

// Constructor + Destructor

GUI::Button::Button()
{
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

	// update MousePos
	this->MousePos = sf::Mouse::getPosition(*window);
}

// styleButton
void GUI::Button::changeStyle(std::map<std::string, float> a)
{
	this->currentStyle = a;
	this->ButtonObject.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->ButtonObject.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->ButtonObject.setPosition(a["PositionX"], a["PositionY"]);
	this->ButtonObject.setOutlineThickness(a["OutlineThickness"]);
	this->ButtonObject.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
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

	sf::Vector2f pos;
	switch (int(style["PositionX"]))
	{
	case (1):
		pos.x = int(this->style["PositionX"] + (this->style["sizeX"] - width) / 2 - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	case (2):
		pos.x = int(this->style["PositionX"] - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	case (3):
		pos.x = int(this->style["PositionX"] + this->style["sizeX"] - width - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	default:
		pos.x = int(this->style["PositionX"] + (this->style["sizeX"] - width) / 2 - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	}

	switch (int(style["PositionY"]))
	{
	case (1):
		pos.y = int(this->style["PositionY"] + (this->style["sizeY"] - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	case (2):
		pos.y = int(this->style["PositionY"] - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	case (3):
		pos.y = int(this->style["PositionY"] + this->style["sizeY"] - height - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	default:
		pos.y = int(this->style["PositionY"] + (this->style["sizeY"] - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	}
	this->text.setPosition(pos);
}

//------Slider------//

void GUI::Slider::render(sf::RenderWindow *window)
{
	// Bar
	window->draw(this->Bar);

	// Handle
	window->draw(this->Handle);

	// update MousePos
	this->MousePos = sf::Mouse::getPosition(*window);
}

// Constructor + Destructor
GUI::Slider::Slider(float rangeStart, float rangeEnd)
{

	this->rangeStart = rangeStart;
	this->rangeEnd = rangeEnd;
	this->value = rangeStart;
}

GUI::Slider::~Slider()
{
}

void GUI::Slider::interpolateStyleBar()
{

	for (auto v1 : this->currentStyleBar)
	{
		for (auto v2 : this->activeStyleBar)
		{

			if (v1.first == v2.first && this->currentStyleBar[v1.first] != this->activeStyleBar[v1.first])
			{
				this->currentStyleBar[v1.first] += ((this->activeStyleBar[v1.first] - this->currentStyleBar[v1.first]) / this->interpolationDuration);
			}
		}
	}

	changeStyleBar(this->currentStyleBar);
}

void GUI::Slider::setActiveStyleBar(std::map<std::string, float> a)
{
	if (lastActiveStyleBar != activeStyleBar)
	{
		this->currentStyleBar["interpolation"] = 1;
	}
	this->lastActiveStyleBar = this->activeStyleBar;
	this->activeStyleBar = a;
	this->activeStyleBar["interpolation"] = 2;
}

void GUI::Slider::changeStyleBar(std::map<std::string, float> a)
{
	this->currentStyleBar = a;
	this->Bar.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->Bar.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->Bar.setPosition(a["PositionX"], a["PositionY"]);
	this->Bar.setOutlineThickness(a["OutlineThickness"]);
	this->Bar.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
}

void GUI::Slider::interpolateStyleHandle()
{

	for (auto v1 : this->currentStyleHandle)
	{
		for (auto v2 : this->activeStyleHandle)
		{

			if (v1.first == v2.first && this->currentStyleHandle[v1.first] != this->activeStyleHandle[v1.first])
			{
				this->currentStyleHandle[v1.first] += ((this->activeStyleHandle[v1.first] - this->currentStyleHandle[v1.first]) / this->interpolationDuration);
			}
		}
	}

	changeStyleHandle(this->currentStyleHandle);
}

void GUI::Slider::setActiveStyleHandle(std::map<std::string, float> a)
{
	if (lastActiveStyleHandle != activeStyleHandle)
	{
		this->currentStyleHandle["interpolation"] = 1;
	}
	this->lastActiveStyleHandle = this->activeStyleHandle;
	this->activeStyleHandle = a;
	this->activeStyleHandle["interpolation"] = 2;
}

void GUI::Slider::changeStyleHandle(std::map<std::string, float> a)
{
	this->currentStyleHandle = a;
	this->Handle.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->Handle.setRadius(a["radius"]);
	this->Handle.setOutlineThickness(a["OutlineThickness"]);
	this->Handle.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
}

void GUI::Slider::setStyleBar(std::map<std::string, float> a)
{
	this->styleBar = a;
	this->currentStyleBar = a;
	this->activeStyleBar = a;
	this->lastActiveStyleBar = a;
	this->HoverStyleBar = a;
	this->changeStyleBar(a);
}

void GUI::Slider::setHoverStyleBar(std::map<std::string, float> a)
{
	this->HoverStyleBar = this->styleBar;
	std::swap(this->HoverStyleBar, a);
	this->HoverStyleBar.insert(a.begin(), a.end());
}

void GUI::Slider::setClickedStyleBar(std::map<std::string, float> a)
{
	this->ClickedStyleBar = this->styleBar;
	std::swap(this->ClickedStyleBar, a);
	this->ClickedStyleBar.insert(a.begin(), a.end());
}

void GUI::Slider::setStyleHandle(std::map<std::string, float> a)
{
	this->styleHandle = a;
	this->currentStyleHandle = a;
	this->activeStyleHandle = a;
	this->lastActiveStyleHandle = a;
	this->HoverStyleHandle = a;
	this->changeStyleHandle(a);
	this->Handle.setPosition(this->styleBar["PositionX"] - this->styleHandle["radius"], this->styleBar["PositionY"] + this->styleBar["sizeY"] / 2 - this->styleHandle["radius"]);
}

void GUI::Slider::setHoverStyleHandle(std::map<std::string, float> a)
{
	this->HoverStyleHandle = this->styleHandle;
	std::swap(this->HoverStyleHandle, a);
	this->HoverStyleHandle.insert(a.begin(), a.end());
}

void GUI::Slider::setClickedStyleHandle(std::map<std::string, float> a)
{
	this->ClickedStyleHandle = this->styleHandle;
	std::swap(this->ClickedStyleHandle, a);
	this->ClickedStyleHandle.insert(a.begin(), a.end());
}

void GUI::Slider::updateHandlePos()
{
	getValue();
	this->setActiveStyleBar(this->ClickedStyleBar);
	this->setActiveStyleHandle(this->ClickedStyleHandle);
	xPos = MousePos.x - this->styleHandle["radius"];
	if (xPos > this->styleBar["PositionX"] + this->styleBar["sizeX"] - this->styleHandle["radius"])
	{
		xPos = this->styleBar["PositionX"] + this->styleBar["sizeX"] - this->styleHandle["radius"];
	}
	else if (xPos < this->styleBar["PositionX"] - this->styleHandle["radius"])
	{
		xPos = this->styleBar["PositionX"] - this->styleHandle["radius"];
	}
	this->Handle.setPosition(xPos, this->styleBar["PositionY"] + this->styleBar["sizeY"] / 2 - this->styleHandle["radius"]);
}

bool GUI::Slider::update(bool MouseButton)
{
	if (ceilf(this->currentStyleBar["interpolation"] * 10.0) / 10.0 != ceilf(this->activeStyleBar["interpolation"] * 10.0) / 10.0)
	{
		this->interpolateStyleBar();
		this->interpolateStyleHandle();
	}
	if (this->MousePos.x > styleBar["PositionX"] - styleBar["OutlineThickness"] && this->MousePos.x < styleBar["PositionX"] + styleBar["sizeX"] + styleBar["OutlineThickness"] && this->MousePos.y > styleBar["PositionY"] - styleBar["OutlineThickness"] && this->MousePos.y < styleBar["PositionY"] + styleBar["sizeY"] + styleBar["OutlineThickness"])
	{

		if (MouseButton)
		{
			this->updateHandlePos();
			handleActive = true;
			return true;
		}
		else
		{
			this->setActiveStyleBar(this->HoverStyleBar);
			this->setActiveStyleHandle(this->HoverStyleHandle);
		}
	}
	else
	{
		if (MouseButton && handleActive)
		{
			this->updateHandlePos();
			return true;
		}
		else
		{
			handleActive = false;
			this->setActiveStyleBar(this->styleBar);
			this->setActiveStyleHandle(this->styleHandle);
		}
	}
	return false;
}

float GUI::Slider::getValue()
{
	value = (xPos - styleBar["PositionX"]) / styleBar["sizeX"] + 0.052;
	value = abs(ceilf(this->value * 1000.0) / 1000.0);
	if (rangeStart <= rangeEnd)
	{
		value = abs(rangeStart - rangeEnd) * value + rangeStart;
	}
	else
	{
		value = abs(rangeEnd - rangeStart) * (1 - value) + rangeEnd;
	}

	return value;
}

//-----Text----//

GUI::Text::Text(sf::RenderWindow *window, std::string text, sf::Font font, std::map<std::string, float> style)
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

	sf::Vector2f pos;
	switch (int(style["PositionX"]))
	{
	case (1):
		pos.x = int((window->getSize().x - width) / 2 - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	case (2):
		pos.x = int(-(this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	case (3):
		pos.x = int(window->getSize().x - width - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	default:
		pos.x = int((window->getSize().x - width) / 2 - (this->text.getCharacterSize() * 0.089) + style["OffsetX"]);
		break;
	}

	switch (int(style["PositionY"]))
	{
	case (1):
		pos.y = int((window->getSize().y - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	case (2):
		pos.y = int(-(this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	case (3):
		pos.y = int(window->getSize().y - height - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	default:
		pos.y = int((window->getSize().y - height) / 2 - (this->text.getCharacterSize() * 0.29) + style["OffsetY"]);
		break;
	}
	this->text.setPosition(pos);
}

void GUI::Text::setString(std::string text)
{
	this->text.setString(text);
}

void GUI::Text::render(sf::RenderWindow *window)
{
	this->text.setFont(this->font);
	window->draw(this->text);
}

GUI::Rect::Rect(std::map<std::string, float> a)
{
	this->rect.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->rect.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->rect.setPosition(a["PositionX"], a["PositionY"]);
	this->rect.setOutlineThickness(a["OutlineThickness"]);
	this->rect.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
}

void GUI::Rect::render(sf::RenderWindow *window)
{
	window->draw(this->rect);
}

void GUI::Rect::setPosition(float X, float Y)
{
	this->rect.setPosition(X, Y);
}

sf::Vector2f GUI::Rect::getPosition()
{
	return this->rect.getPosition();
}

void GUI::Rect::setStyle(std::map<std::string, float> a)
{
	this->rect.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->rect.setSize(sf::Vector2f(a["sizeX"], a["sizeY"]));
	this->rect.setPosition(a["PositionX"], a["PositionY"]);
	this->rect.setOutlineThickness(a["OutlineThickness"]);
	this->rect.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
}

GUI::Circle::Circle(std::map<std::string, float> a)
{
	this->circle.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->circle.setRadius(a["radius"]);
	this->circle.setPosition(a["PositionX"], a["PositionY"]);
	this->circle.setOutlineThickness(a["OutlineThickness"]);
	this->circle.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
}

void GUI::Circle::render(sf::RenderWindow *window)
{
	window->draw(this->circle);
}

void GUI::Circle::setPosition(float X, float Y)
{
	this->circle.setPosition(X, Y);
}

sf::Vector2f GUI::Circle::getPosition()
{
	return this->circle.getPosition();
}

void GUI::Circle::setStyle(std::map<std::string, float> a)
{
	this->circle.setFillColor(sf::Color(a["ColorR"], a["ColorG"], a["ColorB"], a["ColorA"]));
	this->circle.setRadius(a["radius"]);
	this->circle.setPosition(a["PositionX"], a["PositionY"]);
	this->circle.setOutlineThickness(a["OutlineThickness"]);
	this->circle.setOutlineColor(sf::Color(a["OutlineColorR"], a["OutlineColorG"], a["OutlineColorB"], a["ColorA"]));
}
