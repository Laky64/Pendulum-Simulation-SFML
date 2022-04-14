#include <iostream>
#include "../include/Game.h"
#include "../include/PhysicsObject.h"
#include "../include/GUI.h"
#include <iterator>
#include <algorithm>
#include <map>
#include <string>
#include "math.h"
#include <random>

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

    // calc FPS
    currentTime = clock.getElapsedTime();
    fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
    previousTime = currentTime;
}

//--initialize--//
void Game::initVariables()
{

    this->window = nullptr;
    if (!font.loadFromFile("../assets/font.ttf"))
    {
        sf::err() << "Couldn't load font\n";
    }

    previousTime = clock.getElapsedTime();
}

void Game::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->window = new sf::RenderWindow(sf::VideoMode(1440, 1100), "Main", sf::Style::Close, settings);
    this->window->setFramerateLimit(165);
}

void Game::initGameObjects()
{
    //----//
    prefab.setLenght(700);
    this->prefab.setPos(0.00001);
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
    spawnButton.setStyle(GUI::Style::Normal({"sizeX: 110",
                                             "sizeY: 60",
                                             "PositionX: 20",
                                             "PositionY: 805",
                                             "OutlineThickness: 0",
                                             "Color: (234,249,217,100)",
                                             "OutlineColor: (30,30,30,255)"}));
    resetButton.setStyle(GUI::Style::Normal({"sizeX: 110",
                                             "sizeY: 60",
                                             "PositionX: 160",
                                             "PositionY: 805",
                                             "OutlineThickness: 0",
                                             "Color: (109,114,195,100)",
                                             "OutlineColor: (30,30,30,255)"}));

    // set Hovered Style
    spawnButton.setHoverStyle(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                  "OutlineColor: (50,150,50,255)",
                                                  "OutlineThickness: 4"}));
    resetButton.setHoverStyle(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                  "OutlineColor: (150,50,50,255)",
                                                  "OutlineThickness: 4"}));

    // set clicked Style
    spawnButton.setClickedStyle(GUI::Style::Normal({"Color: (20,200,20,255)",
                                                    "OutlineColor: (50,50,50,255)",
                                                    "OutlineThickness: 1"}));
    resetButton.setClickedStyle(GUI::Style::Normal({"Color: (200,20,20,255)",
                                                    "OutlineColor: (50,50,50,255)",
                                                    "OutlineThickness: 1"}));

    // set text, font and Style of text
    spawnButton.setText("Spawn", this->font, GUI::Style::Text({"Size: 30", "Color: (0,0,0,255)", "LetterSpace: 1"}));
    resetButton.setText("Reset", this->font, GUI::Style::Text({"Size: 30", "Color: (0,0,0,255)", "LetterSpace: 1"}));

    // add Button to List
    this->ButtonsList.push_back(spawnButton);
    this->ButtonsList.push_back(resetButton);

    //--Slider--//
    // create new Slider
    GUI::Slider startPositionSlider = GUI::Slider(0.00001, 1.99999);

    // set the name of function to execute, when pressed
    startPositionSlider.functionName = "startPosition";

    // set default Style
    startPositionSlider.setStyleBar(GUI::Style::Normal({"sizeX: 250",
                                                        "sizeY: 5",
                                                        "PositionX: 25",
                                                        "PositionY: 930",
                                                        "OutlineThickness: 4",
                                                        "Color: (255,255,255,100)",
                                                        "OutlineColor: (30,30,30,100)"}));

    // set Hovered Style
    startPositionSlider.setHoverStyleBar(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                             "OutlineColor: (150,150,150,255)",
                                                             "OutlineThickness: 2"}));

    // set clicked Style
    startPositionSlider.setClickedStyleBar(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                               "OutlineColor: (50,50,50,255)",
                                                               "OutlineThickness: 1.4"}));

    // set default Style
    startPositionSlider.setStyleHandle(GUI::Style::Normal({"radius: 13",
                                                           "OutlineThickness: 2",
                                                           "Color: (200,200,200,255)",
                                                           "OutlineColor: (30,30,30,255)"}));

    // set Hovered Style
    startPositionSlider.setHoverStyleHandle(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                                "OutlineColor: (150,50,50,255)",
                                                                "OutlineThickness: 4"}));

    // set clicked Style
    startPositionSlider.setClickedStyleHandle(GUI::Style::Normal({"Color: (150,150,150,255)",
                                                                  "OutlineColor: (150,50,50,255)",
                                                                  "OutlineThickness: 2"}));

    // add Button to List
    this->SliderList.push_back(startPositionSlider);

    // create new Slider
    GUI::Slider lenghtSlider = GUI::Slider(700, 1);

    // set the name of function to execute, when pressed
    lenghtSlider.functionName = "lenght";

    // set default Style
    lenghtSlider.setStyleBar(GUI::Style::Normal({"sizeX: 250",
                                                 "sizeY: 5",
                                                 "PositionX: 25",
                                                 "PositionY: 1010",
                                                 "OutlineThickness: 4",
                                                 "Color: (255,255,255,100)",
                                                 "OutlineColor: (30,30,30,100)"}));

    // set Hovered Style
    lenghtSlider.setHoverStyleBar(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                      "OutlineColor: (150,150,150,255)",
                                                      "OutlineThickness: 2"}));

    // set clicked Style
    lenghtSlider.setClickedStyleBar(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                        "OutlineColor: (50,50,50,255)",
                                                        "OutlineThickness: 1.4"}));

    // set default Style
    lenghtSlider.setStyleHandle(GUI::Style::Normal({"radius: 13",
                                                    "OutlineThickness: 2",
                                                    "Color: (200,200,200,255)",
                                                    "OutlineColor: (30,30,30,255)"}));

    // set Hovered Style
    lenghtSlider.setHoverStyleHandle(GUI::Style::Normal({"Color: (250,250,250,255)",
                                                         "OutlineColor: (150,50,50,255)",
                                                         "OutlineThickness: 4"}));

    // set clicked Style
    lenghtSlider.setClickedStyleHandle(GUI::Style::Normal({"Color: (150,150,150,255)",
                                                           "OutlineColor: (150,50,50,255)",
                                                           "OutlineThickness: 2"}));

    // add Button to List
    this->SliderList.push_back(lenghtSlider);

    //---Text---//
    GUI::Text FPStext(this->window, "FPS:", this->font, GUI::Style::Text({"Size: 30", "Color: (0,0,0,255)", "LetterSpace: 1", "PositionX: Left", "PositionY: Bottom", "OffsetX: 15", "OffsetY: -15"}));
    FPStext.name = "FPS";
    this->TextList.push_back(FPStext);

    GUI::Text SliderAngle(this->window, "Angle", this->font, GUI::Style::Text({"Size: 25", "Color: (0,0,0,255)", "LetterSpace: 1", "PositionX: Left", "PositionY: Bottom", "OffsetX: 15", "OffsetY: -185"}));
    this->TextList.push_back(SliderAngle);

    GUI::Text SliderLenght(this->window, "Lenght", this->font, GUI::Style::Text({"Size: 25", "Color: (20,20,20,255)", "LetterSpace: 1", "PositionX: Left", "PositionY: Bottom", "OffsetX: 15", "OffsetY: -105"}));
    this->TextList.push_back(SliderLenght);

    //--Empty--//
    GUI::Rect GUIBackround(GUI::Style::Normal({"sizeX: 300",
                                               "sizeY: 356",
                                               "PositionX: 4",
                                               "PositionY: 740",
                                               "OutlineThickness: 4",
                                               "Color: (204,199,185,255)",
                                               "OutlineColor: (30,30,30,100)"}));
    this->RectList.push_back(GUIBackround);
    GUI::Rect PendulumBackround(GUI::Style::Normal({"sizeX: 1432",
                                                    "sizeY: 785",
                                                    "PositionX: 4",
                                                    "PositionY: 4",
                                                    "OutlineThickness: 4",
                                                    "Color: (39,39,39,255)",
                                                    "OutlineColor: (30,30,30,100)"}));
    this->RectList.push_back(PendulumBackround);

    this->Background = new GUI::Rect(GUI::Style::Normal({"sizeX:" + std::to_string(1440 - 308),
                                                         "sizeY:" + std::to_string(305),
                                                         "PositionX:" + std::to_string(308),
                                                         "PositionY:" + std::to_string(794),
                                                         "Color: (39,39,39,255)"}));
    this->Background->render(this->window);

    GUI::Circle FixPoint(GUI::Style::Normal({"radius: 5",
                                             "PositionX: 715",
                                             "PositionY: -5",
                                             "Color: (150,150,150,255)",
                                             "OutlineColor: (30,30,30,155)",
                                             "OutlineThickness: 2"

    }));
    this->CircleList.push_back(FixPoint);
}

//--Update--//

//-Called by main--//
void Game::update()
{
    // Events
    this->pollEvents();

    // GUI
    if (MousePosition.x < 300 && MousePosition.y > 700)
    {
        this->updateGUI();
    }
    // GameObjects
    this->updateGameObjects();
}

//-functions-//
void Game::updateGameObjects()
{
    // update PhysicsObject

    for (std::pair<PhysicsObject *, Graph *> it : this->gameObjectsList)
    {
        it.first->updateObject();
        sf::Vector2f a = it.first->getVelocity();
        it.second->update(sqrt(a.x * a.x + a.y * a.y));
    }

    //--Text--//
    for (GUI::Text &it : this->TextList)
    {
        if (it.name == "FPS")
        {
            it.setString("FPS: " + std::to_string(int(this->fps)));
        }
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
                for (std::pair<PhysicsObject *, Graph *> it : this->gameObjectsList)
                {
                    delete it.first;
                    delete it.second;
                }
                // clear List of PhysicsObjects
                this->gameObjectsList = {};

                this->Background->render(this->window);
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
            if (it.functionName == "startPosition")
            {

                //-Prefab-//
                this->prefab.setPos(it.getValue());
            }
            else if (it.functionName == "lenght")
            {

                //-Prefab-//
                this->prefab.setLenght(it.getValue());
            }
        }
    }
}

//-spawn a new GameObject-//
void Game::spawnPhysicsObject()
{
    //--PhysicsObjects--//
    this->Background->render(this->window);
    // create new PhysicsObject with Pointer
    PhysicsObject *ball = new PhysicsObject(20, 0.07f, 67);

    // set the Position
    ball->setPosition(prefab.getPos().x, prefab.getPos().y);

    // set the Color
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 255.0);

    unsigned int r = dist(mt);
    unsigned int g = dist(mt);
    unsigned int b = dist(mt);
    ball->setColor(sf::Color(r, g, b, 255));

    // Add object to List
    int size = gameObjectsList.size() + 1;
    int count = 0;
    Graph *graph = new Graph(this->window, 308, 1440, 794 + (305 / size) * count, (305 / size), 8, sf::Color(r, g, b, 255));
    this->gameObjectsList.insert({ball, graph});
    // count++;
    for (std::pair<PhysicsObject *, Graph *> it : this->gameObjectsList)
    {

        it.second->setPositions(308, 1440, 794 + (305.0 / size) * (count), (305.0 / size), 8);
        it.second->clear(this->window);

        count++;
    }
}

//--render--// -> Called by main
void Game::render()
{
    // clear screen
    // this->window->clear(sf::Color(60, 60, 60, 255));

    //--Empty--//
    for (GUI::Rect &it : this->RectList)
    {
        it.render(this->window);
    }
    for (GUI::Circle &it : this->CircleList)
    {
        it.render(this->window);
    }

    //--PhysicsObjects--//
    for (std::pair<PhysicsObject *, Graph *> it : this->gameObjectsList)
    {
        it.first->renderObject(this->window);
        it.second->render(this->window);
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

    //--Text--//
    for (GUI::Text &it : this->TextList)
    {
        it.render(this->window);
    }

    //-Prefab-//
    this->prefab.render(this->window);

    // display screen
    this->window->display();
}
