#include <iostream>
#include "../include/Game.h"
#include "../include/PhysicsObject.h"
#include "../include/GUI.h"
#include <iterator>
#include <algorithm>
#include <map>
#include <string>

//----Constructor / Destructor----//

Game::Game()
{
    // initialize
    this->initVariables();
    this->initWindow();
    this->initGameObjects();
    this->initGUI();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//------Functions------//
//---Voids---//

//--Events--//
void Game::pollEvents()
{

    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            if (this->event.key.code == sf::Mouse::Left)

                pressMouseLeft = true;
            break;
        case sf::Event::MouseButtonReleased:
            if (this->event.key.code == sf::Mouse::Left)
                pressMouseLeft = false;
            break;
        }
    }

    // update Mouse Position
    MousePosition = sf::Mouse::getPosition(*this->window);
}

//--initialize--//
void Game::initVariables()
{

    this->window = nullptr;
    if (!font.loadFromFile("../assets/font.ttf"))
    {
        sf::err() << "Couldn't load font\n";
    }
}

void Game::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Main", sf::Style::Close, settings);
    this->window->setFramerateLimit(165);
}

void Game::initGameObjects()
{
    //----//
}

void Game::initGUI()
{
    //--Buttons--//
    // create new Button
    GUI::Button spawnButton = GUI::Button();
    GUI::Button resetButton = GUI::Button();

    // set the name of function to execute, when pressed
    spawnButton.functionName = "spawn";
    resetButton.functionName = "reset";

    // set default Style
    spawnButton.setStyle(GUI::Style::Button({"sizeX: 110",
                                             "sizeY: 60",
                                             "PositionX: 30",
                                             "PositionY: 10",
                                             "OutlineThickness: 2",
                                             "Color: (200,200,200)",
                                             "OutlineColor: (30,30,30)"}));
    resetButton.setStyle(GUI::Style::Button({"sizeX: 110",
                                             "sizeY: 60",
                                             "PositionX: 30",
                                             "PositionY: 90",
                                             "OutlineThickness: 2",
                                             "Color: (200,200,200)",
                                             "OutlineColor: (30,30,30)"}));

    // set Hovered Style
    spawnButton.setHoverStyle(GUI::Style::Button({"Color: (250,250,250)",
                                                  "OutlineColor: (50,150,50)",
                                                  "OutlineThickness: 4"}));
    resetButton.setHoverStyle(GUI::Style::Button({"Color: (250,250,250)",
                                                  "OutlineColor: (150,50,50)",
                                                  "OutlineThickness: 4"}));

    // set clicked Style
    spawnButton.setClickedStyle(GUI::Style::Button({"Color: (20,200,20)",
                                                    "OutlineColor: (50,50,50)",
                                                    "OutlineThickness: 1"}));
    resetButton.setClickedStyle(GUI::Style::Button({"Color: (200,20,20)",
                                                    "OutlineColor: (50,50,50)",
                                                    "OutlineThickness: 1"}));

    // set text, font and Style of text
    spawnButton.setText("Spawn", this->font, GUI::Style::Text({"Size: 30", "Color: (0,0,0)", "LetterSpace: 1"}));
    resetButton.setText("Reset", this->font, GUI::Style::Text({"Size: 30", "Color: (0,0,0)", "LetterSpace: 1"}));

    // add Button to List
    this->ButtonsList.push_back(spawnButton);
    this->ButtonsList.push_back(resetButton);

    //--Slider--//
    // create new Slider
    GUI::Slider testSlider = GUI::Slider(-5, 5);

    // set the name of function to execute, when pressed
    testSlider.functionName = "test";

    // set default Style
    testSlider.setStyleBar(GUI::Style::Button({"sizeX: 250",
                                               "sizeY: 5",
                                               "PositionX: 30",
                                               "PositionY: 170",
                                               "OutlineThickness: 4",
                                               "Color: (255,255,255)",
                                               "OutlineColor: (30,30,30)"}));

    // set Hovered Style
    testSlider.setHoverStyleBar(GUI::Style::Button({"Color: (250,250,250)",
                                                    "OutlineColor: (150,150,150)",
                                                    "OutlineThickness: 2"}));

    // set clicked Style
    testSlider.setClickedStyleBar(GUI::Style::Button({"Color: (250,250,250)",
                                                      "OutlineColor: (50,50,50)",
                                                      "OutlineThickness: 1.4"}));

    // set default Style
    testSlider.setStyleHandle(GUI::Style::Button({"radius: 13",
                                                  "OutlineThickness: 2",
                                                  "Color: (200,200,200)",
                                                  "OutlineColor: (30,30,30)"}));

    // set Hovered Style
    testSlider.setHoverStyleHandle(GUI::Style::Button({"Color: (250,250,250)",
                                                       "OutlineColor: (150,50,50)",
                                                       "OutlineThickness: 4"}));

    // set clicked Style
    testSlider.setClickedStyleHandle(GUI::Style::Button({"Color: (250,250,250)",
                                                         "OutlineColor: (150,50,50)",
                                                         "OutlineThickness: 4"}));

    // add Button to List
    this->SliderList.push_back(testSlider);
}

//--Update--//

//-Called by main--//
void Game::update()
{
    // Events
    this->pollEvents();

    // GUI
    this->updateGUI();

    // GameObjects
    this->updateGameObjects();
}

//-functions-//
void Game::updateGameObjects()
{
    // update PhysicsObject
    for (PhysicsObject *it : this->GameObjectsList)
    {
        it->updateObject();
    }
}

void Game::updateGUI()
{
    //--Buttons--//
    for (GUI::Button &it : this->ButtonsList)
    {
        // update Button and get if pressed
        if (it.update(this->pressMouseLeft))
        {
            // get name of function
            if (it.functionName == "spawn")
            {
                // spawn new PhysicsObject
                this->spawnPhysicsObject();
            }
            else if (it.functionName == "reset")
            {
                // delete all Instances of Physicsobject
                for (PhysicsObject *it : this->GameObjectsList)
                {
                    delete it;
                }
                // clear List of PhysicsObjects
                this->GameObjectsList = {};
            };
        }
    }

    //--Slider--//
    for (GUI::Slider &it : this->SliderList)
    {
        // update Button and get if pressed
        if (it.update(this->pressMouseLeft))
        {
            // get name of function
            if (it.functionName == "test")
            {

                it.getValue();
            }
        }
    }
}

//-spawn a new GameObject-//
void Game::spawnPhysicsObject()
{
    //--PhysicsObjects--//

    // create new PhysicsObject with Pointer
    PhysicsObject *ball = new PhysicsObject(20, 0.07f, 67);

    // set the Position
    ball->setPosition(MousePosition.x - ball->getRadius(), MousePosition.y - ball->getRadius());

    // set the Color
    ball->setColor(sf::Color(150, 32, 56, 255));

    // Add object to List
    this->GameObjectsList.push_back(ball);
}

//--render--// -> Called by main
void Game::render()
{
    // clear screen
    this->window->clear(sf::Color(60, 60, 60, 255));

    //--PhysicsObjects--//
    for (PhysicsObject *it : this->GameObjectsList)
    {

        it->renderObject(this->window);
    }

    //----GUI----//

    //--Buttons--//
    for (GUI::Button &it : this->ButtonsList)
    {
        it.render(this->window);
    }

    //--Slider--//
    for (GUI::Slider &it : this->SliderList)
    {
        it.render(this->window);
    }

    // display screen
    this->window->display();
}
