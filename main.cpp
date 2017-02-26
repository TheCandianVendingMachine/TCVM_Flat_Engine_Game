// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <fe/filesystem/fileUtilities.hpp>
#include <iostream>

int main()
    {
        auto first = fe::lastTimeModified("test.txt");

        std::ofstream out("test.txt");
        out << "a";
        out.close();
        
        std::cout << "Difference: " << fe::lastTimeModified("test.txt") - first;

        std::cin.get();
        return 0;
    }