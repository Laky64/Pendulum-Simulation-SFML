#include <iostream>
#include "../include/Game.h"
#include "../include/PhysicsObject.h"
#include "../include/GUI.h"
#include <iterator>
#include <algorithm>
#include <map>
#include <string>
#include "math.h"

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
                                             "PositionY: 790",
                                             "OutlineThickness: 2",
                                             "Color: (200,200,200,100)",
                                             "OutlineColor: (30,30,30,255)"}));
    resetButton.setStyle(GUI::Style::Normal({"sizeX: 110",
                                             "sizeY: 60",
                                             "PositionX: 160",
                                             "PositionY: 790",
                                             "OutlineThickness: 2",
                                             "Color: (200,200,200,100)",
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
    GUI::Text FPStext(this->window, "FPS:", this->font, GUI::Style::Text({"Size: 30", "Color: (0,0,0,255)", "LetterSpace: 1", "PositionX: Left", "PositionY: Bottom", "OffsetX: 15", "OffsetY: -15",

                                                                          "OutlineColor: (50,50,50,200)", "OutlineThickness: 1"}));
    FPStext.name = "FPS";
    this->TextList.push_back(FPStext);

    GUI::Text SliderAngle(this->window, "Angle", this->font, GUI::Style::Text({"Size: 25", "Color: (0,0,0,255)", "LetterSpace: 1", "PositionX: Left", "PositionY: Bottom", "OffsetX: 15", "OffsetY: -185",

                                                                               "OutlineColor: (50,50,50,200)", "OutlineThickness: 1"}));
    this->TextList.push_back(SliderAngle);

    GUI::Text SliderLenght(this->window, "Lenght", this->font, GUI::Style::Text({"Size: 25", "Color: (20,20,20,255)", "LetterSpace: 1", "PositionX: Left", "PositionY: Bottom", "OffsetX: 15", "OffsetY: -105",

                                                                                 "OutlineColor: (50,50,50,200)", "OutlineThickness: 1"}));
    this->TextList.push_back(SliderLenght);

    //--Empty--//
    GUI::Rect GraphBackround(GUI::Style::Normal({"sizeX: 1432",
                                                 "sizeY: 356",
                                                 "PositionX: 4",
                                                 "PositionY: 740",
                                                 "OutlineThickness: 4",
                                                 "Color: (255,255,255,100)",
                                                 "OutlineColor: (30,30,30,100)"}));
    this->RectList.push_back(GraphBackround);

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

    //--Text--//
    for (GUI::Text &it : this->TextList)
    {
        if (it.name == "FPS")
        {
            it.setString("FPS: " + std::to_string(int(this->fps)));
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
    ball->setPosition(prefab.getPos().x, prefab.getPos().y);

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

    //--Empty--//
    for (GUI::Rect &it : this->RectList)
    {
        it.render(this->window);
    }
    for (GUI::Circle &it : this->CircleList)
    {
        it.render(this->window);
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
