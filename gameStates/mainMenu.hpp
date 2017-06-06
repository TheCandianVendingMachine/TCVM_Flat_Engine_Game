// mainMenu.hpp
// the main menu
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/subsystems/resourceManager/resourceManager.hpp>
#include <fe/gui/panel.hpp>
#include <SFML/Graphics/Font.hpp>

class mainMenu : public fe::baseGameState
    {
        private:
            fe::gui::panel m_gui;

        public:
            void init();

            void deinit();
    };