#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <string>
#include <stdarg.h>
#include <functional>


namespace GUI {
	
	class Style {
	public:
		static std::map<std::string, float> Button(std::initializer_list<std::string> list);
		static std::map<std::string, float> Text(std::initializer_list<std::string> list);

	};	

	class Button
	{
	private:
		sf::Font font;
		sf::Text text;
		sf::Vector2i MousePos;
		sf::RectangleShape ButtonObject;
		std::map<std::string, float> style;
		std::map<std::string, float> HoverStyle;
		std::map<std::string, float> ClickedStyle;


		bool leftMouseButton = false;

		std::map<std::string, float> currentStyle;
		std::map<std::string, float> lastActiveStyle;
		std::map<std::string, float> activeStyle;
		float interpolationDuration = 20;
		void setActiveStyle(std::map<std::string, float> a);
		void interpolateStyle();
		void changeStyle(std::map<std::string, float> a);
		

	public:
		//Constructors / Destructors
		
		Button();
		virtual ~Button();
		bool update(bool MouseButton);
		bool getState();	
		void render(sf::RenderWindow* window);
		void setStyle(std::map<std::string,float> a);
		void setHoverStyle(std::map<std::string, float> a);
		void setClickedStyle(std::map<std::string, float> a);
		void setText(std::string text, sf::Font font, std::map<std::string, float> style);

		std::string functionName = "";
		
	};

	class Slider
	{
	private:
		sf::RectangleShape Bar;
		sf::CircleShape Handle;
		sf::Vector2i MousePos;

		float xPos = 0;
		bool handleActive = false;

		float interpolationDuration = 20;

		std::map<std::string, float> styleBar;
		std::map<std::string, float> HoverStyleBar;
		std::map<std::string, float> ClickedStyleBar;

		std::map<std::string, float> currentStyleBar;
		std::map<std::string, float> lastActiveStyleBar;
		std::map<std::string, float> activeStyleBar;

		void setActiveStyleBar(std::map<std::string, float> a);
		void interpolateStyleBar();
		void changeStyleBar(std::map<std::string, float> a);


		std::map<std::string, float> styleHandle;
		std::map<std::string, float> HoverStyleHandle;
		std::map<std::string, float> ClickedStyleHandle;

		std::map<std::string, float> currentStyleHandle;
		std::map<std::string, float> lastActiveStyleHandle;
		std::map<std::string, float> activeStyleHandle;

		void setActiveStyleHandle(std::map<std::string, float> a);
		void interpolateStyleHandle();
		void changeStyleHandle(std::map<std::string, float> a);

		bool leftMouseButton = false;

		void updateHandlePos();

		float value;
		float rangeStart;
		float rangeEnd;
	public:
		//Constructors / Destructors
		Slider(float rangeStart, float rangeEnd);	

		virtual ~Slider();
		bool update(bool MouseButton);
		void render(sf::RenderWindow* window);

		void setStyleBar(std::map<std::string, float> a);
		void setHoverStyleBar(std::map<std::string, float> a);
		void setClickedStyleBar(std::map<std::string, float> a);

		void setStyleHandle(std::map<std::string, float> a);
		void setHoverStyleHandle(std::map<std::string, float> a);
		void setClickedStyleHandle(std::map<std::string, float> a);

		float getValue();	

		std::string functionName = "";
	};

	class Text {
	private:
		sf::Font font;
		sf::Text text;
	public:
		Text(sf::RenderWindow* window, std::string text, sf::Font font, std::map<std::string, float> style);
		void render(sf::RenderWindow* window);
		void setString(std::string text);
		std::string name;
	};
}


