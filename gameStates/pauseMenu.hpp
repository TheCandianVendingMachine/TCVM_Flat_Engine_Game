// pauseMenu.hpp
// the pause menu
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/gui/panel.hpp>
#include <fe/subsystems/resourceManager/resourceManager.hpp>

#include <SFML/Graphics/Font.hpp>

class pauseMenu : public fe::baseGameState
    {
        private:
            fe::resourceManager<sf::Font> m_font;
            fe::gui::panel m_gui;

            unsigned int m_unpauseKeyHandle;

        public:
            void init();

            void onActive();
            void onDeactive();

            void deinit();
    };