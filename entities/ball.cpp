#include "ball.hpp"
#include "paddle.hpp"
#include <fe/subsystems/gameState/gameState.hpp>

void ball::collision(const fe::collider &collision)
    {
        auto collider = static_cast<const fe::AABB<paddle>&>(collision);
        fe::Vector2d halfSize((collider.m_max / 2.f) + collider.m_position);
        // get line between the ball and the middle of the paddle
        fe::Vector2d differencePos = (getPosition() + (fe::Vector2d(20.f, 20.f) / 2.f)) - halfSize;

        m_velocity = differencePos.normalize() * (m_speed * (rand() % 3));
        if (abs(m_velocity.x) < 1.f)
            {
                m_velocity.x = m_speed;
            }

        if (differencePos.x > 0.f) 
            {
                setPosition({ collider.m_max.x + collider.m_position.x + 1, getPosition().y });
            }
        else
            {
                setPosition({ collider.m_position.x - 20.f - 1.f, getPosition().y });
            }
    }

void ball::setDirection(int dir)
    {
        m_velocity.x = m_speed * dir;
        m_velocity.y = 0;
    }

ball::ball(fe::Vector2d position) : m_speed(300.f)
    {
        m_verticies[0].position = sf::Vector2f(0, 0);
        m_verticies[1].position = sf::Vector2f(20, 0);
        m_verticies[2].position = sf::Vector2f(20, 20);
        m_verticies[3].position = sf::Vector2f(0, 20);

        // set a random direction
        setDirection(rand() % 2);

        setColour(sf::Color::Blue);

        setPosition(position);
    }

void ball::onAdd(fe::baseGameState &state)
    {
        addCollider(state.getCollisionHandler().add<fe::AABB<ball>>(fe::Vector2d(20, 20), this));
    }

void ball::update(float deltaTime)
    {
        if (getPosition().y < 0.f || getPosition().y + 20.f > fe::engine::get().getWindowSize().y)
            {
                m_velocity.y = -m_velocity.y;
            }

        move(m_velocity * deltaTime);
    }