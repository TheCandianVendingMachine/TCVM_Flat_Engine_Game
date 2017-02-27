// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/debug/logger.hpp>
#include <fe/subsystems/memory/memoryManager.hpp>

int main()
    {
        fe::logger log;
        log.startUp("output.txt");

        FE_LOG("Logging to console + output", 123);
        FE_CONSOLE_LOG("Logging to only console", 456);

        fe::memoryManager mm;
        mm.startUp(3, 0);

        mm.alloc(4);

        mm.shutDown();
        log.shutDown();
        std::cin.get();
        return 0;
    }