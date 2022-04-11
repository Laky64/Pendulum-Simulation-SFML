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
		void changeStyle(std::map<std::string, float> a);
		std::function<void()> OnPressFuntion;
		bool leftMouseButton;


	public:
		//Constructors / Destructors
		void setFunction(std::function<void()> a);
		Button();
		virtual ~Button();
		void update(bool MouseButton);
		bool getState();	
		void render(sf::RenderWindow* window);
		void setStyle(std::map<std::string,float> a);
		void setHoverStyle(std::map<std::string, float> a);
		void setText(std::string text, sf::Font font, std::map<std::string, float> style);
		
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


