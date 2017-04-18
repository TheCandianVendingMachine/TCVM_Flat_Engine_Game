#include "gameState.hpp"
#include "../entities/paddle.hpp"
#include "../entities/ball.hpp"
#include "../entities/goal.hpp"

#include <fe/subsystems/messaging/gameEvent.hpp>
#include <fe/subsystems/messaging/eventSender.hpp>
#include <fe/engine.hpp>
#include <fe/gui/label.hpp>
#include <string>

void gameState::init()
    {
        m_lPaddle = addEntity<paddle>(fe::Vector2d(40, 0));
        m_rPaddle = addEntity<paddle>(fe::engine::get().getWindowSize() - fe::Vector2d(40, 0));

        m_ball = addEntity<ball>(fe::engine::get().getWindowSize() / 2.f);

        addEntity<goal>(m_ball, 0, fe::Vector2d(0, 0));
        addEntity<goal>(m_ball, 1, fe::Vector2d(fe::engine::get().getWindowSize().x - 20, 0));

        sf::Font *font = m_fontManager.load("Roboto-Regular.ttf", "RobotFont");
        m_scoreLeftHandle =  m_ui.addElement(new fe::gui::label(*font, "0"));
        m_scoreRightHandle = m_ui.addElement(new fe::gui::label(*font, "0"));

        m_ui.setSize(fe::engine::get().getWindowSize());

        m_ui.getElement(m_scoreLeftHandle)->setPosition({ (fe::engine::get().getWindowSize().x / 2.f) - 50.f, 50.f});
        m_ui.getElement(m_scoreRightHandle)->setPosition({(fe::engine::get().getWindowSize().x / 2.f) + 50.f, 50.f});

        m_ui.setPanelClearColour(sf::Color::Transparent);

        addPanel(&m_ui);

        fe::engine::get().getEventSender()->subscribe(this, 0);
        fe::engine::get().getEventSender()->subscribe(this, 1);
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
                                    std::cout << "Right Goal!\n";
                                    static_cast<fe::gui::label*>(m_ui.getElement(m_scoreRightHandle))->setString(std::to_string(++m_scoreRight).c_str());
                                    break;
                                case 1:
                                    std::cout << "Left Goal!\n";
                                    static_cast<fe::gui::label*>(m_ui.getElement(m_scoreLeftHandle))->setString(std::to_string(++m_scoreLeft).c_str());
                                    break;
                                default:
                                    break;
                            }

                        getEntity(m_lPaddle)->setPosition(fe::Vector2d(40, 0));
                        getEntity(m_rPaddle)->setPosition(fe::engine::get().getWindowSize() - fe::Vector2d(40, 0));

                        getEntity(m_ball)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                        getEntity<ball>(m_ball)->setDirection(0);

                        if (m_scoreLeft >= 1)
                            {
                                m_ui.removeElement(m_scoreLeftHandle);
                                m_ui.removeElement(m_scoreRightHandle);

                                auto handle = m_ui.addElement(new fe::gui::label(*m_fontManager.get("RobotFont"), "Game Over! Left Wins!"));
                                static_cast<fe::gui::label*>(m_ui.getElement(handle))->setCharacterSize(64);
                                m_ui.getElement(handle)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                            }
                        else if (m_scoreRight >= 1)
                            {
                                m_ui.removeElement(m_scoreLeftHandle);
                                m_ui.removeElement(m_scoreRightHandle);

                                auto handle = m_ui.addElement(new fe::gui::label(*m_fontManager.get("RobotFont"), "Game Over! Right Wins!"));
                                static_cast<fe::gui::label*>(m_ui.getElement(handle))->setCharacterSize(64);
                                m_ui.getElement(handle)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                            }
                        else
                            {
                                fe::gameEvent newEvent(1, 1);
                                newEvent.args[0] = event.args[0];
                                fe::engine::get().getEventSender()->send(newEvent, id(), 2000.f);
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
                    }
                    break;
                default:
                    break;
            }
    }

void gameState::deinit()
    {
        m_fontManager.shutDown();
    }
