// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <SFML/Graphics.hpp>

#include "entities/paddle.hpp"
#include "gameStates/gameState.hpp"

void debug()
    {
        fe::memoryManager::get().printDebugInformation();
        std::cout << "\nFPS: " << fe::engine::getFPS() << "\n\n";
    }

int main()
    {
        fe::engine engine;
        engine.startUp();

        gameState game;
        engine.queueState(&game);

        fe::inputManager::get().add(fe::input<sf::Keyboard::Key>(false, true, sf::Keyboard::Tilde, fe::function<void()>(debug)));
        engine.run();

        engine.shutDown();
        return 0;
    }