#include "gameState.hpp"
#include "../entities/paddle.hpp"
#include "../entities/ball.hpp"
#include "../entities/goal.hpp"

#include <fe/subsystems/messaging/gameEvent.hpp>
#include <fe/subsystems/messaging/eventSender.hpp>
#include <fe/engine.hpp>

void gameState::init()
    {
        m_lPaddle = addEntity<paddle>(fe::Vector2d(40, 0));
        m_rPaddle = addEntity<paddle>(fe::engine::get().getWindowSize() - fe::Vector2d(40, 0));

        m_ball = addEntity<ball>(fe::engine::get().getWindowSize() / 2.f);

        addEntity<goal>(m_ball, 0, fe::Vector2d(0, 0));
        addEntity<goal>(m_ball, 1, fe::Vector2d(fe::engine::get().getWindowSize().x - 20, 0));

        fe::engine::get().getEventSender()->subscribe(this, 0);
    }

void gameState::handleEvent(const fe::gameEvent &event)
    {
        int side = event.args[0].arg.TYPE_INTEGER;
        switch (side)
            {
                // left side
                case 0:
                    std::cout << "Right Goal!\n";
                    getEntity(m_ball)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                    getEntity<ball>(m_ball)->setDirection(1);
                    break;
                // right side
                case 1:
                    std::cout << "Left Goal!\n";
                    getEntity(m_ball)->setPosition(fe::engine::get().getWindowSize() / 2.f);
                    getEntity<ball>(m_ball)->setDirection(-1);
                    break;
                default:
                    break;
            }

        getEntity(m_lPaddle)->setPosition(fe::Vector2d(40, 0));
        getEntity(m_rPaddle)->setPosition(fe::engine::get().getWindowSize() - fe::Vector2d(40, 0));
    }
