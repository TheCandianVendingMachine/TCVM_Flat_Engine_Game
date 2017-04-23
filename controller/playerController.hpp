// playerController.hpp
// allows the paddle to be controlled by a player
#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include "entityController.hpp"

class playerController : public entityController
    {
        private:
            sf::Keyboard::Key m_moveUp;
            sf::Keyboard::Key m_moveDown;

        public:
            playerController(paddle *paddle, int playerNumber = 0);
            void enable(bool value);

    };