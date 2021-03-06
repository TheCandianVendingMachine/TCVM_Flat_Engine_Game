#include "gameState.hpp"
#include "../entities/paddle.hpp"
#include "../entities/ball.hpp"
#include "../entities/goal.hpp"

#include "../controller/playerController.hpp"
#include "../controller/aiController.hpp"

#include "mainMenu.hpp"
#include "pauseMenu.hpp"

#include <fe/subsystems/messaging/gameEvent.hpp>
#include <fe/subsystems/messaging/eventSender.hpp>
#include <fe/subsystems/gameState/gameStateMachine.hpp>
#include <fe/engine.hpp>
#include <fe/gui/label.hpp>
#include <string>

gameState::gameState(bool pvp, unsigned int maxScore) : m_pvp(pvp), m_maxScore(maxScore)
    {
    }

void gameState::init()
    {
        m_lPaddle = addEntity<paddle>(fe::Vector2d(40, 0));
        m_rPaddle = addEntity<paddle>(fe::engine::get().getWindowSize() - fe::Vector2d(40, 0));

        m_ball = addEntity<ball>(fe::engine::get().getWindowSize() / 2.f);

        addEntity<goal>(m_ball, 0, fe::Vector2d(0 - 20, 0));
        addEntity<goal>(m_ball, 1, fe::Vector2d(fe::engine::get().getWindowSize().x, 0));

        const sf::Font *font = fe::engine::get().getResourceManager<sf::Font>()->load("Roboto-Regular.ttf", "RobotFont");
        m_scoreLeftHandle =  m_ui.addElement(new fe::gui::label(*font, "0"));
        m_scoreRightHandle = m_ui.addElement(new fe::gui::label(*font, "0"));

        m_ui.setSize(fe::engine::get().getWindowSize());

        m_ui.getElement(m_scoreLeftHandle)->setPosition({ (fe::engine::get().getWindowSize().x / 2.f) - 50.f, 50.f});
        m_ui.getElement(m_scoreRightHandle)->setPosition({(fe::engine::get().getWindowSize().x / 2.f) + 50.f, 50.f});

        m_ui.setPanelClearColour(sf::Color::Transparent);

        addPanel(&m_ui);

        m_left = new playerController(getEntity<paddle>(m_lPaddle), 0);

        if (m_pvp) 
            {
                m_right = new playerController(getEntity<paddle>(m_rPaddle), 1);
            }
        else
            {
                m_right = new aiController(getEntity<paddle>(m_rPaddle), m_ball);
            }

        getEntity<ball>(m_ball)->setDirection(1);
    }

void gameState::onActive()
    {
        fe::engine::get().getEventSender()->subscribe(this, 0);
        fe::engine::get().getEventSender()->subscribe(this, 1);

        m_pauseKeyHandle = fe::engine::get().getInputManager().add(sf::Keyboard::Escape,
                           fe::input([]() {fe::engine::get().getStateMachine().queuePush<pauseMenu>(fe::gameStateMachine::stateOptions::RENDER_OVERTOP); }, false));
    }

void gameState::handleEvent(const fe::gameEvent &event)
    {
        switch (event.eventType)
            {
                case 0:
                    {
                        int side = event.args[0].arg.TYPE_INTEGER;
                        switch (side)
                            {
                                case 0:
                                    static_cast<fe::gui::label*>(m_ui.getElement(m_scoreRightHandle))->setString(std::to_string(++m_scoreRight).c_str());
                                    break;
                                case 1:
                                    static_cast<fe::gui::label*>(m_ui.getElement(m_scoreLeftHandle))->setString(std::to_string(++m_scoreLeft).c_str());
                                    break;
                                default:
                                    break;
                            }

                        getEntity(m_ball)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                        getEntity<ball>(m_ball)->setDirection(0);

                        m_left->enable(false);
                        m_right->enable(false);

                        if (m_scoreLeft >= m_maxScore)
                            {
                                m_ui.removeElement(m_scoreLeftHandle);
                                m_ui.removeElement(m_scoreRightHandle);

                                auto handle = m_ui.addElement(new fe::gui::label(*fe::engine::get().getResourceManager<sf::Font>()->get("RobotFont"), "Game Over! Left Wins!"));
                                static_cast<fe::gui::label*>(m_ui.getElement(handle))->setCharacterSize(64);
                                m_ui.getElement(handle)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                                m_endGame.start(fe::seconds(3));
                            }
                        else if (m_scoreRight >= m_maxScore)
                            {
                                m_ui.removeElement(m_scoreLeftHandle);
                                m_ui.removeElement(m_scoreRightHandle);

                                auto handle = m_ui.addElement(new fe::gui::label(*fe::engine::get().getResourceManager<sf::Font>()->get("RobotFont"), "Game Over! Right Wins!"));
                                static_cast<fe::gui::label*>(m_ui.getElement(handle))->setCharacterSize(64);
                                m_ui.getElement(handle)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                                m_endGame.start(fe::seconds(3));
                            }
                        else
                            {
                                getEntity(m_lPaddle)->setPosition(fe::Vector2d(40, 0));
                                getEntity(m_rPaddle)->setPosition(fe::engine::get().getWindowSize() - fe::Vector2d(40, 0));

                                fe::gameEvent newEvent(1, 1);
                                newEvent.args[0] = event.args[0];
                                fe::engine::get().getEventSender()->send(newEvent, id(), 1000.f);
                            }
                    }
                    break;
                case 1:
                    {
                        int side = event.args[0].arg.TYPE_INTEGER;
                        switch (side)
                            {
                                // left side
                                case 0:
                                    getEntity<ball>(m_ball)->setDirection(1);
                                    break;
                                // right side
                                case 1:
                                    getEntity<ball>(m_ball)->setDirection(-1);
                                    break;
                                default:
                                    break;
                            }

                        m_left->enable(true);
                        m_right->enable(true);
                    }
                    break;
                default:
                    break;
            }
    }

void gameState::preUpdate()
    {
        if (m_endGame.isDone())
            {
                fe::engine::get().getStateMachine().queuePop();
                fe::engine::get().getStateMachine().queuePush<mainMenu>();
            }
        else
            {
                m_left->update();
                m_right->update();
            }
    }

void gameState::onDeactive()
    {
        fe::engine::get().getInputManager().removeObject(m_pauseKeyHandle);
        fe::engine::get().getEventSender()->unsubscribe(this, 0);
        fe::engine::get().getEventSender()->unsubscribe(this, 1);
    }

void gameState::deinit()
    {}
