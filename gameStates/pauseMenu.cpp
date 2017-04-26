#include "pauseMenu.hpp"
#include "mainMenu.hpp"

#include <fe/gui/label.hpp>
#include <fe/gui/button.hpp>
#include <fe/subsystems/gameState/gameStateMachine.hpp>
#include <fe/engine.hpp>

void pauseMenu::init()
    {
        auto pauseText = m_gui.addElement(new fe::gui::label(*m_font.get("robot"), "Paused"));
        auto resumeText = m_gui.addElement(new fe::gui::label(*m_font.get("robot"), "Resume"));
        auto exitMenuText = m_gui.addElement(new fe::gui::label(*m_font.get("robot"), "Exit to Menu"));

        auto resumeButton = m_gui.addElement(new fe::gui::button(fe::Vector2d(150, 30), []() {fe::engine::get().getStateMachine().queuePop(); }));
        auto exitToMenu = m_gui.addElement(new fe::gui::button(fe::Vector2d(150, 30), []() {fe::engine::get().getStateMachine().clear(); fe::engine::get().getStateMachine().queuePush<mainMenu>(); }));

        m_gui.getElement(resumeText)->setParent(m_gui.getElement(resumeButton));
        m_gui.getElement(exitMenuText)->setParent(m_gui.getElement(exitToMenu));

        m_gui.setElementPosition(resumeButton, fe::Vector2d(0.5, 0.5));
        m_gui.setElementPosition(exitMenuText, fe::Vector2d(0.5, 0.55));

        m_gui.setElementPosition(pauseText, fe::Vector2d(0.5, 0.4));

        static_cast<fe::gui::label*>(m_gui.getElement(pauseText))->setCharacterSize(48);
    }
