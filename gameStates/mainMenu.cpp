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
        auto title = m_gui.addElement(new fe::gui::label(*font, "Flat Engine Pong"));
        static_cast<fe::gui::label*>(m_gui.getElement(title))->setCharacterSize(72);
        m_gui.setElementPosition(title, { 0.5f, 0.15f });

        auto startButtonHandle = m_gui.addElement(new fe::gui::button(fe::Vector2d(200, 35), []() { fe::engine::get().getStateMachine().queuePop(); fe::engine::get().getStateMachine().queuePush<gameState>(); }));
        auto startLabelHandle = m_gui.addElement(new fe::gui::label(*font, "Start Game"));

        auto startButton = m_gui.getElement(startButtonHandle);
        auto startLabel = m_gui.getElement(startLabelHandle);

        startLabel->setParent(startButton);
        startLabel->setPosition(startButton->getSize() / 2.f);

        m_gui.setElementPosition(startButtonHandle, fe::Vector2d(0.5f, 0.5f));

        addPanel(&m_gui);
    }

void mainMenu::deinit()
    {
    }
