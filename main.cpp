// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <fe/subsystems/filesystem/fileUtilities.hpp>

int main()
    {
        std::cout << "All files in directory and subdirectories\n";
        auto ret = fe::getAllFilesInDirectory("../");
        for (auto &file : ret)
            {
                std::cout << file << "\n";
            }

        std::cout << "\nAll files in directory and subdirectories with extension .cpp\n";
        ret = fe::getAllFilesInDirectory("../", ".cpp");
        for (auto &file : ret)
            {
                std::cout << file << "\n";
            }

        std::cout << "\nAll files in single directory\n";
        ret = fe::getFilesInDirectory("../");
        for (auto &file : ret)
            {
                std::cout << file << "\n";
            }

        std::cout << "\nAll files in directory with extension .sln\n";
        ret = fe::getFilesInDirectory("../", ".sln");
        for (auto &file : ret)
            {
                std::cout << file << "\n";
            }

        std::cin.get();
        return 0;
    }