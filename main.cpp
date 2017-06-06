// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <SFML/Graphics.hpp>

#include "gameStates/gameState.hpp"
#include "gameStates/mainMenu.hpp"
#include <fe/subsystems/gameState/gameStateMachine.hpp>

#include <fe/engine.hpp>
#include <fe/subsystems/input/inputManager.hpp>

int main()
    {
        fe::engine engine;
        engine.startUp(64_MiB, 50_MiB);

        engine.getStateMachine().queuePush<mainMenu>();

        engine.run();

        engine.shutDown();
        return 0;
    }