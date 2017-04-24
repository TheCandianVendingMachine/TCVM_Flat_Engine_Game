#include "mainMenu.hpp"
#include "gameState.hpp"

#include <fe/gui/label.hpp>
#include <fe/gui/button.hpp>
#include <fe/subsystems/gameState/gameStateMachine.hpp>
#include <fe/engine.hpp>

void mainMenu::init()
    {
        m_gui.setSize(fe::engine::get().getWindowSize());

        sf::Font *font = m_font.load("Roboto-Regular.ttf", "RobotFont");
        auto but = m_gui.addElement(new fe::gui::button(fe::Vector2d(64, 32), []() { fe::engine::get().getStateMachine().queuePop(); fe::engine::get().getStateMachine().queuePush<gameState>(); }));
        auto label = m_gui.addElement(new fe::gui::label(*font, "Test1"));

        m_gui.getElement(label)->setParent(m_gui.getElement(but));
        m_gui.setElementPosition(but, fe::Vector2d(0.5f, 0.5f));

        addPanel(&m_gui);
    }

void mainMenu::deinit()
    {
    }
