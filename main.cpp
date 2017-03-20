// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fe/engine.hpp>
#include <fe/subsystems/gameState/gameState.hpp>

#include "entities/paddle.hpp"

class gameState : public fe::baseGameState
    {
        private:
        public:
            void init()
                {
                    addEntity<paddle>(fe::Vector2d(40, 0));
                }
    };

fe::engine engine;

void debug()
    {
        fe::memoryManager::get().printDebugInformation();
        std::cout << "\nFPS: " << engine.getFPS() << "\n\n";
    }

int main()
    {
        engine.startUp();

        gameState game;
        engine.queueState(&game);

        fe::inputManager::get().add(fe::input<sf::Keyboard::Key>(false, true, sf::Keyboard::Tilde, fe::function<void()>(debug)));
        engine.run();

        engine.shutDown();
        return 0;
    }