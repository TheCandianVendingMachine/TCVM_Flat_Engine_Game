#include "ball.hpp"

void ball::onCollision(const fe::collider &collision)
    {
        m_speed.x = -m_speed.x;
    }

ball::ball(fe::Vector2d position) : m_bounds(getPosition(), { 20, 20 })
    {
        m_verticies[0].position = sf::Vector2f(0, 0);
        m_verticies[1].position = sf::Vector2f(20, 0);
        m_verticies[2].position = sf::Vector2f(20, 20);
        m_verticies[3].position = sf::Vector2f(0, 20);

        m_speed.x = -100.f;

        setColour(sf::Color::Blue);

        setPosition(position);
        m_bounds.m_callback = fe::function<void, ball, const fe::collider&>(fe::fPtr<true, ball, void, const fe::collider&>(this, &ball::onCollision));
    }

void ball::update(float deltaTime)
    {
        move(m_speed * deltaTime);
    }

const fe::collider &ball::getCollider()
    {
        return m_bounds;
    }
