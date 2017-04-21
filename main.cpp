// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <SFML/Graphics.hpp>

#include "gameStates/gameState.hpp"
#include "gameStates/mainMenu.hpp"
#include <fe/subsystems/gameState/gameStateMachine.hpp>

#include <fe/engine.hpp>
#include <fe/subsystems/input/inputManager.hpp>
#include <exception>

// remove console in release builds
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


void debug()
    {
        fe::memoryManager::get().printDebugInformation();
        std::cout << "\nFPS: " << fe::engine::get().getFPS() << "\n\n";
    }


int main()
    {
        fe::engine engine;
        engine.startUp();

        engine.getStateMachine().queuePush<mainMenu>();

        fe::inputManager::get().add("debug", fe::input<sf::Keyboard::Key>(false, true, sf::Keyboard::Tilde, debug));

        engine.run();

        engine.shutDown();
        return 0;
    }