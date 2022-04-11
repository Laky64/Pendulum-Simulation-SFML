// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Game.h"

int main()
{
    // init GameEngine
    Game game;
    Game* ptr = &game;
    game.ptr = ptr;

    // Game loop
    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}
