#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <list>
#include "PhysicsObject.h"
#include "GUI.h"
#include "Prefab.h"
#include "Graph.h"

class Game
{
private:

	//-Window-//
	sf::RenderWindow* window;
	
	//-Event-//
	sf::Event event;

	//Game Objects
	std::map<PhysicsObject*, Graph*> gameObjectsList;


	//--GUI--//	
	GUI::Rect* Background;
	bool reset;
	sf::Font font;

	//-ButtonList-//
	std::list<GUI::Button> ButtonsList;
	//-SliderList-//
	std::list<GUI::Slider> SliderList;
	//-TextList-//
	std::list<GUI::Text> TextList;
	//-Rect-//
	std::list<GUI::Rect> RectList;
	//-Circle-//
	std::list<GUI::Circle> CircleList;

	//-PrefabObject-//
	Prefab prefab;


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

	//-timing-fps-//
	float fps;
	sf::Clock clock;
	sf::Time previousTime;
	sf::Time currentTime;

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
