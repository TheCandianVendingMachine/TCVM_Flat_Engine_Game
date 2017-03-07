// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/engine.hpp>

int main()
    {
        fe::engine engine;
        engine.startUp();

        engine.run();

        engine.shutDown();
        return 0;
    }