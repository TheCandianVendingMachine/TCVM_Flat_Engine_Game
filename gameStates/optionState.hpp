// optionState.hpp
// options for hte game
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/gui/panel.hpp>

class optionState : public fe::baseGameState
    {
        private:
            fe::gui::panel m_gui;
            bool m_aiMode;

        public:
            void init();
            void deinit();

    };