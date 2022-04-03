#include <iostream>
#include "../include/Game.h"
#include "../include/PhysicsObject.h"
#include <iterator>
#include <algorithm>

// Private Functions
void Game::initVariables()
{
    this->window = nullptr;
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

// Constructors / Destructors

Game::Game()
{

    this->initVariables();
    this->initWindow();
    this->initGameObjects();
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
                spawnPhysicsObject();
        }
    }
    MousePosition = sf::Mouse::getPosition(*this->window);
}

// Update
void Game::updateGameObjects()
{

    for (PhysicsObject &it : this->GameObjectsList)
    {
        it.updateObject();
    }
}

void Game::spawnPhysicsObject()
{
    PhysicsObject ball(20, 0.07f, 67);
    ball.setPosition(MousePosition.x - ball.getRadius(), MousePosition.y - ball.getRadius());
    ball.setColor(sf::Color(150, 32, 56, 255));
    this->GameObjectsList.push_back(ball);
    // std::cout << "Ball:" << ball.getColor().r << ", " << ball.getColor().g << std::endl;
    // std::cout << "Mouse:" << MousePosition.x << ", " << MousePosition.y << std::endl;
}

void Game::update()
{
    // Update Events
    this->updateGameObjects();
    this->pollEvents();
}

void Game::render()
{
    this->window->clear(sf::Color(40, 40, 40, 255)); // claer screen

    for (PhysicsObject &it : this->GameObjectsList)
    {

        it.renderObject(this->window);
    }

    this->window->display(); // done drawing
}
