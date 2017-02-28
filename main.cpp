// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/subsystems/memory/memoryManager.hpp>
#include <fe/subsystems/resourceManager/resourceObject.hpp>
#include <fe/subsystems/resourceManager/resourceManager.hpp>
#include <fe/debug/logger.hpp>

int main()
    {
        fe::memoryManager memManager;
        fe::logger logger;
        fe::resourceManager resourceManager;

        ///////
        memManager.startUp(sizeof(char) * 1024, sizeof(char) * 512);
        logger.startUp("output.txt");
        resourceManager.startUp(1);

        resourceManager.add("test", "test.png", fe::resourceObjectType::RESOURCE_TEXTURE);

        logger.shutDown();
        memManager.shutDown();
        ////////
        std::cin.get();
        return 0;
    }