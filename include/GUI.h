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
		sf::Vertex testLine[2];
		sf::Vector2i MousePos;
		sf::RectangleShape ButtonObject;
		std::map<std::string, float> style;
		std::map<std::string, float> HoverStyle;
		std::map<std::string, float> ClickedStyle;

		std::function<void()> OnPressFuntion;
		bool leftMouseButton;

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
		void render();


	public:
		//Constructors / Destructors
		Slider();
		virtual ~Slider();
		void update();
		float getValue();
	};

}


