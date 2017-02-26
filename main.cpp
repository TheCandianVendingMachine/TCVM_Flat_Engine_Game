// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <fe/time/time.hpp>
#include <fe/time/clock.hpp>
#include <fe/time/countdown.hpp>
#include <iostream>
#include <thread>

int main()
    {
        fe::clock test;
        fe::countdown count;
        count.start(fe::seconds(1));

        // Prints 0.500
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        test.stop(true);
        std::cout << test.getTime().asSeconds() << "\n";

        // Prints 0, 500
        std::cout << "Done: " << count.isDone() << " " << count.timeUntilCompletion().asMilliseconds() << "\n";

        // Prints 0.500
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        test.stop(false);
        std::cout << test.getTime().asSeconds() << "\n";

        // Prints 1
        std::cout << "Done: " << count.isDone() << "\n";
        count.start(fe::milliseconds(500));

        // Prints 0.750
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::cout << test.getTime().asSeconds() << "\n";

        // Prints epoch
        std::cout << fe::clock::getTimeSinceEpoch().asSeconds() << "\n";

        // Prints current date
        std::cout << fe::clock::getFormattedTime("%c %Z") << "\n";

        // Prints 0, 250
        std::cout << "Done: " << count.isDone() << " " << count.timeUntilCompletion().asMilliseconds() << "\n";

        std::cin.get();
        return 0;
    }