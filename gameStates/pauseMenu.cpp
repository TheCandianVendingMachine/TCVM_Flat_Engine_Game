#include "pauseMenu.hpp"
#include "mainMenu.hpp"

#include <fe/gui/label.hpp>
#include <fe/gui/button.hpp>
#include <fe/subsystems/gameState/gameStateMachine.hpp>
#include <fe/subsystems/input/input.hpp>
#include <fe/subsystems/input/inputManager.hpp>
#include <fe/engine.hpp>

void pauseMenu::init()
    {
        const sf::Font *font = fe::engine::get().getResourceManager<sf::Font>()->load("Roboto-Regular.ttf", "robot");
        auto resumeButton = m_gui.addElement(new fe::gui::button(fe::Vector2d(200, 35), []() {fe::engine::get().getStateMachine().queuePop(); }));
        auto exitToMenu = m_gui.addElement(new fe::gui::button(fe::Vector2d(200, 35), []() {fe::engine::get().getStateMachine().queueClear(); fe::engine::get().getStateMachine().queuePush<mainMenu>(); }));

        auto pauseText = m_gui.addElement(new fe::gui::label(*font, "Paused"));
        auto resumeText = m_gui.addElement(new fe::gui::label(*font, "Resume"));
        auto exitMenuText = m_gui.addElement(new fe::gui::label(*font, "Exit to Menu"));

        m_gui.setSize(fe::engine::get().getWindowSize());

        m_gui.getElement(resumeText)->setParent(m_gui.getElement(resumeButton));
        m_gui.getElement(exitMenuText)->setParent(m_gui.getElement(exitToMenu));

        m_gui.setElementPosition(resumeButton, fe::Vector2d(0.5, 0.5));
        m_gui.setElementPosition(exitToMenu, fe::Vector2d(0.5, 0.58));
        m_gui.setElementPosition(pauseText, fe::Vector2d(0.5, 0.15));

        m_gui.getElement(resumeText)->setPosition(fe::Vector2d(200, 35) / 2.f);
        m_gui.getElement(exitMenuText)->setPosition(fe::Vector2d(200, 35) / 2.f);

        static_cast<fe::gui::label*>(m_gui.getElement(pauseText))->setCharacterSize(48);

        m_gui.setPanelClearColour(sf::Color::Transparent);
        addPanel(&m_gui);
    }

void pauseMenu::onActive()
    {
        m_unpauseKeyHandle = fe::inputManager::get().add(sf::Keyboard::Escape,
                             fe::input([]() { fe::engine::get().getStateMachine().queuePop(); }, false));
    }

void pauseMenu::onDeactive()
    {
        fe::inputManager::get().removeObject(m_unpauseKeyHandle);
    }

void pauseMenu::deinit()
    {}
