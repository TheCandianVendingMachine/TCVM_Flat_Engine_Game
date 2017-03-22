// paddle.hpp
// a paddle entity
#pragma once
#include <fe/entity/baseEntity.hpp>
#include <fe/subsystems/input/inputManager.hpp>
#include <fe/collision/colliders.hpp>
#include <fe/engine.hpp>

class paddle : public fe::baseEntity
    {
        private:
            fe::AABB m_bounds;
            fe::Vector2d m_speed;

            void moveUp() { m_speed.y = -200.f; }
            void moveDown() { m_speed.y = 200.f; }

            void onCollision() { std::cout << "a\n"; }

        public:
            paddle(fe::Vector2d position) : m_bounds(getPosition(), {20, 150})
                {
                    m_verticies[0].position = sf::Vector2f(0, 0);
                    m_verticies[1].position = sf::Vector2f(20, 0);
                    m_verticies[2].position = sf::Vector2f(20, 150);
                    m_verticies[3].position = sf::Vector2f(0, 150);

                    setColour(sf::Color::Blue);

                    setPosition(position);

                    fe::inputManager::get().add<paddle>(fe::input<sf::Keyboard::Key, paddle*>(true, true, sf::Keyboard::Up, fe::function<void(paddle*)>(this, &paddle::moveUp)));
                    fe::inputManager::get().add<paddle>(fe::input<sf::Keyboard::Key, paddle*>(true, true, sf::Keyboard::Down, fe::function<void(paddle*)>(this, &paddle::moveDown)));

                    m_bounds.m_callback = fe::function<void(paddle*)>(this, &paddle::onCollision).getFPtr();
                }

            void update(float deltaTime)
                {
                    move(m_speed * deltaTime);
                    m_speed = fe::Vector2d();
                    
                    if (getPosition().y + 150.f > fe::engine::getWindowSize().y)
                        {
                            setPosition({ getPosition().x, fe::engine::getWindowSize().y - 150.f });
                        }

                    if (getPosition().y < 0.f)
                        {
                            setPosition({ getPosition().x, 0.f });
                        }
                }

            const fe::collider &getCollider() { return m_bounds; }
    };