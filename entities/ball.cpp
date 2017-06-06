#include "ball.hpp"
#include "paddle.hpp"
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/collision/collisionData.hpp>
#include <functional>

void ball::collision(fe::collisionData &collision)
    {
        auto collider = static_cast<fe::AABB*>(collision.m_collider);

        fe::Vector2d halfSize((collider->m_max / 2.f) + collider->m_position);
        // get line between the ball and the middle of the paddle
        fe::Vector2d differencePos = (getPosition() + (fe::Vector2d(20.f, 20.f) / 2.f)) - halfSize;
        
        float dot = differencePos.normalize().dot(fe::Vector2d(1, 0));

        if (abs(dot) > 0.4f) 
            {
                m_velocity = differencePos.normalize() * (m_speed / abs(dot));
            }
        else
            {
                m_velocity = differencePos.normalize() * m_speed;
            }

        if (abs(m_velocity.x) < 1.f)
            {
                m_velocity.x = m_speed;
            }

        if (differencePos.x > 0.f) 
            {
                setPosition({ collider->m_max.x + collider->m_position.x + 1, getPosition().y });
            }
        else
            {
                setPosition({ collider->m_position.x - 20.f - 1.f, getPosition().y });
            }
    }

void ball::setDirection(int dir)
    {
        m_velocity.x = m_speed * dir;
        m_velocity.y = 0;
    }

fe::Vector2d ball::getVelocity()
    {
        return m_velocity;
    }

ball::ball(fe::Vector2d position) : m_speed(300.f)
    {
        setVertSize({20, 20});

        // set a random direction
        setDirection(rand() % 2);

        setColour(sf::Color::Blue);

        setPosition(position);
    }

void ball::onAdd(fe::baseGameState &state)
    {
        addCollider(state.getCollisionHandler().add<fe::AABB>(fe::Vector2d(20, 20), std::bind(&ball::collision, this, std::placeholders::_1)));
    }

void ball::update(float deltaTime)
    {
        if (getPosition().y < 0.f || getPosition().y + 20.f > fe::engine::get().getWindowSize().y)
            {
                m_velocity.y = -m_velocity.y;
            }

        move(m_velocity * deltaTime);
    }