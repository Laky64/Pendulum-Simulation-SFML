#include <iostream>
#include "../include/Game.h"
#include "../include/PhysicsObject.h"
#include "../include/GUI.h"
#include <iterator>
#include <algorithm>
#include <map>
#include <string>

// Private Functions
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
    this->videoMode.width = 1600;
    this->videoMode.height = 900;
    this->window = new sf::RenderWindow(this->videoMode, "Main", sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(165);
}

void Game::initGameObjects()
{
}

void Game::initGUI()
{

    GUI::Button spawnButton = GUI::Button();

    spawnButton.functionName = "spawn";

    spawnButton.setStyle(GUI::Style::Button({"sizeX: 90",
                                             "sizeY: 50",
                                             "PositionX: 30",
                                             "PositionY: 10",
                                             "OutlineThickness: 2",
                                             "Color: (200,200,200)",
                                             "OutlineColor: (30,30,30)"}));

    spawnButton.setHoverStyle(GUI::Style::Button({"Color: (250,250,250)",
                                                  "OutlineColor: (50,150,50)",
                                                  "OutlineThickness: 4"}));
    spawnButton.setClickedStyle(GUI::Style::Button({"Color: (20,200,20)",
                                                    "OutlineColor: (50,50,50)",
                                                    "OutlineThickness: 1"}));

    spawnButton.setText("  Spawn", this->font, GUI::Style::Button({"Size: 20", "Color: (0,0,0)"}));

    this->ButtonsList.push_back(spawnButton);

    GUI::Button resetButton = GUI::Button();

    resetButton.functionName = "reset";

    resetButton.setStyle(GUI::Style::Button({"sizeX: 90",
                                             "sizeY: 50",
                                             "PositionX: 30",
                                             "PositionY: 70",
                                             "OutlineThickness: 2",
                                             "Color: (200,200,200)",
                                             "OutlineColor: (30,30,30)"}));

    resetButton.setHoverStyle(GUI::Style::Button({"Color: (250,250,250)",
                                                  "OutlineColor: (150,50,50)",
                                                  "OutlineThickness: 4"}));
    resetButton.setClickedStyle(GUI::Style::Button({"Color: (200,20,20)",
                                                    "OutlineColor: (50,50,50)",
                                                    "OutlineThickness: 1"}));
    resetButton.setText("  Reset", this->font, GUI::Style::Button({"Size: 20", "Color: (0,0,0)"}));

    this->ButtonsList.push_back(resetButton);
}

// Constructors / Destructors

Game::Game()
{

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

// Functions
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
    // GUI::MousePos = MousePosition;
}

// Update
void Game::updateGameObjects()
{

    for (PhysicsObject *it : this->GameObjectsList)
    {
        it->updateObject();
    }
}

void Game::updateGUI()
{

    for (GUI::Button &it : this->ButtonsList)
    {
        if (it.update(this->pressMouseLeft))
        {
            if (it.functionName == "spawn")
            {
                this->spawnPhysicsObject();
            }
            if (it.functionName == "reset")
            {
                for (PhysicsObject *it : this->GameObjectsList)
                {
                    delete it;
                }
                this->GameObjectsList = {};
            };
        }
    }
}

void Game::spawnPhysicsObject()
{
    PhysicsObject *ball = new PhysicsObject(20, 0.07f, 67);
    ball->setPosition(MousePosition.x - ball->getRadius(), MousePosition.y - ball->getRadius());
    ball->setColor(sf::Color(150, 32, 56, 255));
    this->GameObjectsList.push_back(ball);
    // std::cout << "Ball:" << ball.getColor().r << ", " << ball.getColor().g << std::endl;
    // std::cout << "Mouse:" << MousePosition.x << ", " << MousePosition.y << std::endl;
}

void Game::update()
{
    // Update Events
    this->updateGameObjects();
    this->pollEvents();
    this->updateGUI();
}

void Game::render()
{
    this->window->clear(sf::Color(60, 60, 60, 255)); // claer screen

    for (PhysicsObject *it : this->GameObjectsList)
    {

        it->renderObject(this->window);
    }

    for (GUI::Button &it : this->ButtonsList)
    {
        it.render(this->window);
    }
    sf::RectangleShape rectangle;

    this->window->display(); // done drawing
}
