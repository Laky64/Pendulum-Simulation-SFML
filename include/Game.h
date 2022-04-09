#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <list>
#include "PhysicsObject.h"
#include "GUI.h"
/*
	Game Engine Class
	Wrapper Class

*/

class Game
{
private:
	//Variables
	// GameObjects
	// PhysicsObjPos

	//Window

	sf::VideoMode videoMode;
	sf::Event event;

	//Game Objects

	std::list<PhysicsObject> GameObjectsList = {};

	std::list<GUI::Button> ButtonsList = {};

	//Private functions
	void pollEvents();
	void initVariables();
	void initWindow();
	void initGameObjects();	
	void initGUI();
	void updateGameObjects();
	void updateGUI();
	void spawnPhysicsObject();
	const float G = .05f;

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();



	//Accessors
	const bool running() const;
	sf::RenderWindow* window;
	sf::Vector2i MousePosition;
	//Functions
	
	void update();
	void render();

};
