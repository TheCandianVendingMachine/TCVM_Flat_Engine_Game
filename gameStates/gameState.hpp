// gameState.hpp
// the main state that updates all entities
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/subsystems/messaging/eventHandler.hpp>
#include <fe/subsystems/resourceManager/resourceManager.hpp>
#include <fe/gui/panel.hpp>
#include <fe/time/countdown.hpp>

#include <SFML/Graphics/Font.hpp>

#include "../controller/entityController.hpp"

class gameState : public fe::baseGameState, public fe::eventHandler
    {
        private:
            fe::gui::panel m_ui;
            fe::resourceManager<sf::Font> m_fontManager;

            fe::countdown m_endGame;

            entityController *m_left;
            entityController *m_right;

            unsigned int m_maxScore;

            unsigned int m_scoreLeftHandle;
            unsigned int m_scoreRightHandle;

            unsigned int m_scoreLeft;
            unsigned int m_scoreRight;

            unsigned int m_ball;

            unsigned int m_lPaddle;
            unsigned int m_rPaddle;

        public:
            void init();
            void handleEvent(const fe::gameEvent &event);

            void preUpdate();

            void deinit();

    };