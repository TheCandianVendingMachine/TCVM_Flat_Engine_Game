// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/subsystems/memory/memoryManager.hpp>

int main()
    {
        fe::memoryManager memManager;
        memManager.startUp();

        int *unsafeAlloc = static_cast<int*>(FE_ALLOC_UNSAFE(sizeof(int)));
        *unsafeAlloc = 15;

        auto markerFirst = fe::memoryManager::get().getStackAllocater().getMarker();
        int *stackAllocBeforeMarker = static_cast<int*>(FE_ALLOC_STACK(sizeof(int)));
        *stackAllocBeforeMarker = 30;

        auto marker = fe::memoryManager::get().getStackAllocater().getMarker();
        int *stackAllocAfterMarker = static_cast<int*>(FE_ALLOC_STACK(sizeof(int)));
        *stackAllocAfterMarker = 45;

        std::cout << unsafeAlloc << " " << stackAllocBeforeMarker << " " << stackAllocAfterMarker << "\n";
        std::cout << *unsafeAlloc << " " << *stackAllocBeforeMarker << " " << *stackAllocAfterMarker << "\n\n";

        // Shows how freeing the stack to a marker doesnt invalidate pointers
        FE_FREE_STACK(marker);
        std::cout << unsafeAlloc << " " << stackAllocBeforeMarker << " " << stackAllocAfterMarker << "\n";
        std::cout << *unsafeAlloc << " " << *stackAllocBeforeMarker << " " << *stackAllocAfterMarker << "\n\n";

        // Shows how once you free the stack you can overwrite the data
        float *stackFree = static_cast<float*>(FE_ALLOC_STACK(sizeof(float)));
        *stackFree = 60.f;

        std::cout << unsafeAlloc << " " << stackAllocBeforeMarker << " " << stackAllocAfterMarker << " " << stackFree << "\n";
        std::cout << *unsafeAlloc << " " << *stackAllocBeforeMarker << " " << *stackAllocAfterMarker << " " << *stackFree << "\n\n";

        // Shows how freeing the stack doesnt invalidate pointers, it only allows them to be overwritten
        FE_FREE_STACK(markerFirst);

        std::cout << unsafeAlloc << " " << stackAllocBeforeMarker << " " << stackAllocAfterMarker << " " << stackFree << "\n";
        std::cout << *unsafeAlloc << " " << *stackAllocBeforeMarker << " " << *stackAllocAfterMarker << " " << *stackFree << "\n\n";

        memManager.shutDown();

        // Shows how we can't show the data anymore since it has been freed
        std::cout << unsafeAlloc << " " << stackAllocBeforeMarker << " " << stackAllocAfterMarker << " " << stackFree << "\n";

        std::cin.get();
        return 0;
    }