#include "aiController.hpp"
#include "../entities/paddle.hpp"
#include "../entities/ball.hpp"

#include <fe/engine.hpp>
#include <fe/subsystems/gameState/gameStateMachine.hpp>
#include <fe/subsystems/gameState/gameState.hpp>

aiController::aiController(paddle *paddle, unsigned int ball) : entityController(paddle), m_ballHandle(ball)
    {
    }

void aiController::update()
    {
        if (m_enabled)
            {
                auto ballPosition = fe::engine::get().getCurrentState().getEntity(m_ballHandle)->getPosition();
                auto ballVel = fe::engine::get().getCurrentState().getEntity<ball>(m_ballHandle)->getVelocity();

                fe::Vector2d futurePosition = ((ballVel * 10.f * fe::engine::get().getDeltaTime()) + ballPosition);
                if (futurePosition.y > m_controlling->getPosition().y + (m_controlling->getSize().y / 2.f) + 5.f) // 5 = buffer to make AI not jitter
                    {
                        m_controlling->moveDown();
                    }
                else if (futurePosition.y < m_controlling->getPosition().y + (m_controlling->getSize().y / 2.f) - 5.f)
                    {
                        m_controlling->moveUp();
                    }

            }
    }
