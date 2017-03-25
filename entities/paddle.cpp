#include "paddle.hpp"
#include <fe/subsystems/gameState/gameState.hpp>

paddle::paddle(fe::Vector2d position)   : m_speed(300.f)
    {
        m_verticies[0].position = sf::Vector2f(0, 0);
        m_verticies[1].position = sf::Vector2f(20, 0);
        m_verticies[2].position = sf::Vector2f(20, 150);
        m_verticies[3].position = sf::Vector2f(0, 150);

        setColour(sf::Color::Blue);

        setPosition(position);

        fe::inputManager::get().add<paddle>(fe::input<sf::Keyboard::Key, paddle>(true, true, sf::Keyboard::Up, fe::function<void, paddle>(fe::fPtr<true, paddle, void>(this, &paddle::moveUp))));
        fe::inputManager::get().add<paddle>(fe::input<sf::Keyboard::Key, paddle>(true, true, sf::Keyboard::Down, fe::function<void, paddle>(fe::fPtr<true, paddle, void>(this, &paddle::moveDown))));
    }

void paddle::onAdd(fe::baseGameState &state)
    {
        addCollider(state.getCollisionHandler().add<fe::AABB<paddle>>(fe::Vector2d(20, 150), this));
    }

void paddle::update(float deltaTime)
    {
        move(m_velocity * deltaTime);
        m_velocity = fe::Vector2d();

        if (getPosition().y + 150.f > fe::engine::getWindowSize().y)
            {
                setPosition({ getPosition().x, fe::engine::getWindowSize().y - 150.f });
            }

        if (getPosition().y < 0.f)
            {
                setPosition({ getPosition().x, 0.f });
            }
    }
