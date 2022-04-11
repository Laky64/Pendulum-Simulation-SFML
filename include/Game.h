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
	sf::RenderWindow* window;
	
	sf::VideoMode videoMode;
	sf::Event event;

	//Game Objects

	std::list<PhysicsObject> GameObjectsList;

	std::list<GUI::Button> ButtonsList;

	sf::Font font;
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

	static void OnPressReset();
	static void OnPressSpawn();


public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	static Game* ptrSta;
	Game* ptr;
	//Accessors
	const bool running() const;
	
	sf::Vector2i MousePosition;
	//Functions
	
	void update();
	void render();
	void setInstance();

	bool pressMouseLeft;

};
