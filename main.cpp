// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <fe/time/time.hpp>
#include <fe/time/clock.hpp>
#include <iostream>
#include <thread>

int main()
    {
        fe::clock test;

        // Prints 0.500
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        test.stop(true);
        std::cout << test.getTime().asSeconds() << "\n";

        // Prints 0.500
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        test.stop(false);
        std::cout << test.getTime().asSeconds() << "\n";

        // Prints 0.750
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::cout << test.getTime().asSeconds() << "\n";

        // Prints epoch
        std::cout << fe::clock::getTimeSinceEpoch().asSeconds() << "\n";

        // Prints current date
        std::cout << fe::clock::getCurrentTime("%c %Z");

        std::cin.get();
        return 0;
    }