// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "gameStates/mainMenu.hpp"
#include <fe/subsystems/gameState/gameStateMachine.hpp>

#include <fe/engine.hpp>

int main()
    {
        fe::engine engine;
        engine.startUp(128_MiB, 100_MiB);

        engine.getStateMachine().queuePush<mainMenu>();

        engine.run();

        engine.shutDown();
        return 0;
    }