#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <list>
#include "PhysicsObject.h"
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
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//Game Objects

	std::list<PhysicsObject> GameObjectsList = {};

	//Private functions
	void pollEvents();
	void initVariables();
	void initWindow();
	void initGameObjects();
	void updateGameObjects();
	void spawnPhysicsObject();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	const float G = .05f;

	//Accessors
	const bool running() const;

	//Functions
	
	void update();
	void render();

	sf::Vector2i MousePosition;
};
