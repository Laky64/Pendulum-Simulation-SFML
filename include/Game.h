#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <list>
#include "PhysicsObject.h"
#include "GUI.h"

class Game
{
private:

	//-Window-//
	sf::RenderWindow* window;
	
	//-Event-//
	sf::Event event;

	//Game Objects

	std::list<PhysicsObject*> GameObjectsList;


	//--GUI--//	

	sf::Font font;

	//-ButtonList-//
	std::list<GUI::Button> ButtonsList;
	//-SliderList-//
	std::list<GUI::Slider> SliderList;

	//--Private functions --//
	//-Events-//
	void pollEvents();

	//-initilize-//
	void initVariables();
	void initWindow();
	void initGameObjects();	
	void initGUI();

	//-update-//
	void updateGameObjects();
	void updateGUI();

	void spawnPhysicsObject();


	//--Private Variables --//
	//Gravition//
	const float G = .05f;

	//-inputs-//
	bool pressMouseLeft;
	sf::Vector2i MousePosition;

public:
	//-Constructors / Destructors-//
	Game();
	virtual ~Game();

	//-Accessors-//
	const bool running() const;
	
	//--Functions called by main--//
	void update();
	void render();
};
