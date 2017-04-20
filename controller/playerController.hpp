// playerController.hpp
// allows the paddle to be controlled by a player
#pragma once
#include <string>
#include "entityController.hpp"

class playerController : public entityController
    {
        private:
            std::string m_moveUp;
            std::string m_moveDown;

        public:
            playerController(paddle *paddle, int playerNumber = 0);
            void enable(bool value);

    };