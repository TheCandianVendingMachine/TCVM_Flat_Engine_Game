// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/subsystems/memory/memoryManager.hpp>
#include <fe/subsystems/memory/poolAllocater.hpp>

int main()
    {
        fe::memoryManager memManager;
        memManager.startUp(sizeof(int) * 5, sizeof(int));

        fe::poolAllocater<int> poolAlloc;
        poolAlloc.startUp(2, memManager.getBuffer());

        int *i = poolAlloc.alloc();
        *i = 5;

        int *j = poolAlloc.alloc();
        *j = 10;

        std::cout << i << " " << *i << " " << j << " " << *j << "\n";

        poolAlloc.clear();
        std::cout << i << " " << *i << " " << j << " " << *j << "\n";

        j = poolAlloc.alloc();
        std::cout << i << " " << *i << " " << j << " " << *j << "\n";

        memManager.shutDown();
        std::cin.get();
        return 0;
    }