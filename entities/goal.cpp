#include "goal.hpp"
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/subsystems/messaging/eventSender.hpp>
#include <fe/engine.hpp>

goal::goal(fe::sceneGraph::EntityHandle ball, int goal, fe::Vector2d position) : m_goalSide(goal), m_ball(ball)
    {
        setPosition(position);
    }

void goal::onAdd(fe::baseGameState &state)
    {
        addCollider(state.getCollisionHandler().add<fe::AABB<goal>>(fe::Vector2d(20, fe::engine::get().getWindowSize().y), this));
        enableCollision(false);
    }

void goal::update(float deltaTime)
    {
        if (getCollider().collide(fe::engine::get().getCurrentState().getEntity(m_ball)->getCollider()))
            {
                fe::gameEvent msg(0, 0);
                msg.args[0] = fe::gameEventArgument(m_goalSide);

                fe::engine().get().getEventSender()->send(msg, 0);
            }
    }
