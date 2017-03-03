// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/subsystems/memory/memoryManager.hpp>
#include <fe/debug/logger.hpp>

#include <fe/subsystems/resourceManager/resourceManager.hpp>
#include <fe/debug/profiler.hpp>

fe::memoryManager memManager;
fe::logger logger;

void init()
    {
        logger.startUp("output.txt");
        memManager.startUp(sizeof(char) * 1024, sizeof(char) * 512); 
    }

void deinit()
    {
        logger.shutDown();
        memManager.shutDown();
    }

int main()
    {
        init();

        fe::resourceManager manager;
        manager.startUp(2);
        manager.add("123", "test.png", fe::resourceObjectType::RESOURCE_TEXTURE);

        PROFILE("abc");
        FE_ALLOC_DIRECT("poop", 464);
        END_PROFILE;

        memManager.printDebugInformation();

        deinit();
        std::cin.get();
        return 0;
    }