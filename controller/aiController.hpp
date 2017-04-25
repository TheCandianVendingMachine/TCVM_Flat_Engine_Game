// aiController.hpp
// allows the paddle to be controlled by an AI.
#pragma once
#include "entityController.hpp"

class paddle;

class aiController : public entityController
    {
        private:
            unsigned int m_ballHandle;

        public:
            aiController(paddle *paddle, unsigned int ball);
            void update();

    };