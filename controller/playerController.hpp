// playerController.hpp
// allows the paddle to be controlled by a player
#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include "entityController.hpp"

class playerController : public entityController
    {
        private:
            unsigned int m_upHandle;
            unsigned int m_downHandle;

        public:
            playerController(paddle *paddle, int playerNumber = 0);
            void enable(bool value);

            ~playerController();

    };