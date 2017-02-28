// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/subsystems/memory/memoryManager.hpp>
#include <fe/debug/logger.hpp>

fe::memoryManager memManager;
fe::logger logger;

void init()
    {
        memManager.startUp(sizeof(char) * 1024, sizeof(char) * 512);
        logger.startUp("output.txt");
    }

void deinit()
    {
        logger.shutDown();
        memManager.shutDown();
    }

int main()
    {
        init();



        deinit();
        std::cin.get();
        return 0;
    }