// gameState.hpp
// the main state that updates all entities
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/subsystems/messaging/eventHandler.hpp>

class gameState : public fe::baseGameState, public fe::eventHandler
    {
        private:
            unsigned int m_ball;

            unsigned int m_lPaddle;
            unsigned int m_rPaddle;

        public:
            void init();
            void handleEvent(const fe::gameEvent &event);
    };