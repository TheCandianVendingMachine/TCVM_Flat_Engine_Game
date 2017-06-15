#include "optionState.hpp"
#include "gameState.hpp"
#include <fe/engine.hpp>
#include <fe/gui/button.hpp>
#include <fe/gui/label.hpp>
#include <fe/gui/textBox.hpp>
#include <fe/subsystems/gameState/gameStateMachine.hpp>
#include <fe/subsystems/resourceManager/resourceManager.hpp>

#include "gameState.hpp"

void optionState::init()
    {
        m_aiMode = false;

        m_gui.setSize(fe::engine::get().getWindowSize());
        const sf::Font *font = fe::engine::get().getResourceManager<sf::Font>()->load("Roboto-Regular.ttf", "RobotFont");
        
        /* UI STUFF BELOW LINE */
        fe::Handle gameOptionsText = m_gui.addElement(new fe::gui::label(*font, "Game Options"));
        static_cast<fe::gui::label*>(m_gui.getElement(gameOptionsText))->setCharacterSize(72);

        fe::Handle gameModeButton = m_gui.addElement(new fe::gui::button({ 215, 35 }, [gameOptionsText, this]()
            {
                // we can assure that gameOptionsText is 1 handle behind this one since it was declared just before it
                m_aiMode = !m_aiMode;
                if (m_aiMode) 
                    {
                        static_cast<fe::gui::label*>(m_gui.getElement(gameOptionsText + 2))->setString("Play vs AI");
                    }
                else
                    {
                        static_cast<fe::gui::label*>(m_gui.getElement(gameOptionsText + 2))->setString("Play vs Player");
                    }
            }));
        fe::Handle gameModeText = m_gui.addElement(new fe::gui::label(*font, "Play vs Player"));

        fe::Handle maxScoreInput = m_gui.addElement(new fe::gui::textBox({ 40, 35 }, *font, fe::gui::textBox::options::NUM, 5.f, 2.f, 2, "5"));
        fe::Handle maxScoreText = m_gui.addElement(new fe::gui::label(*font, "Max Score"));

        fe::Handle playButton = m_gui.addElement(new fe::gui::button({ 200, 35 }, [this, maxScoreInput]()
            {
                fe::engine::get().getStateMachine().queuePop();

                unsigned int maxScore = std::stoul(static_cast<fe::gui::textBox*>(m_gui.getElement(maxScoreInput))->getString());
                fe::engine::get().getStateMachine().queuePush<gameState>(fe::gameStateMachine::stateOptions::NONE, !m_aiMode, maxScore);
            }));
        fe::Handle playText = m_gui.addElement(new fe::gui::label(*font, "Start Game"));


        m_gui.getElement(gameModeText)->setParent(m_gui.getElement(gameModeButton));
        m_gui.getElement(gameModeText)->setPosition(m_gui.getElement(gameModeButton)->getSize() / 2.f);

        m_gui.getElement(maxScoreText)->setParent(m_gui.getElement(maxScoreInput));
        m_gui.getElement(maxScoreText)->setPosition({ -75.f, m_gui.getElement(maxScoreInput)->getSize().y / 2.f });

        m_gui.getElement(playText)->setParent(m_gui.getElement(playButton));
        m_gui.getElement(playText)->setPosition(m_gui.getElement(playButton)->getSize() / 2.f);

        m_gui.setElementPosition(gameOptionsText, { 0.5f, 0.15f });
        m_gui.setElementPosition(gameModeButton, {0.5f, 0.4f });
        m_gui.setElementPosition(maxScoreInput, { 0.56f, 0.5f });
        m_gui.setElementPosition(playButton, { 0.5f, 0.6f });
        /* UI STUFF ABOVE LINE */

        addPanel(&m_gui);
    }

void optionState::deinit()
    {
    }
