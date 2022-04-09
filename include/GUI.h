#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <string>
#include <stdarg.h>

namespace GUI {
	
	static class Style {
	public:
		static std::map<std::string, float> Button(std::initializer_list<std::string> list);
	};



	class Button
	{
	private:

		sf::Vector2i MousePos;
		sf::RectangleShape ButtonObject;
		std::map<std::string, float> style;
		std::map<std::string, float> HoverStyle;
		void changeStyle(std::map<std::string, float> a);

	public:
		//Constructors / Destructors
		Button();
		virtual ~Button();
		void update();
		bool getState();	
		void render(sf::RenderWindow* window);
		void setStyle(std::map<std::string,float> a);
		void setHoverStyle(std::map<std::string, float> a);
		
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


