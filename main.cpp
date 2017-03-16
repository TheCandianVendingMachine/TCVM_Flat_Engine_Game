// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fe/engine.hpp>
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/entity/baseEntity.hpp>
#include <fe/math/Vector2.hpp>
#include <fe/debug/profiler.hpp>

class testEntity : public fe::baseEntity
    {
        private:
            sf::VertexArray m_shape;
            fe::Vector2d m_speed;

            void moveRight() { m_speed.x = 200.f; }
            void moveLeft() { m_speed.x = -200.f; }

        public:
            testEntity() : m_shape(sf::PrimitiveType::Quads, 4)
                {
                    m_shape[0].position = sf::Vector2f(0, 0);
                    m_shape[1].position = sf::Vector2f(100, 0);
                    m_shape[2].position = sf::Vector2f(100, 50);
                    m_shape[3].position = sf::Vector2f(0, 50);

                    m_shape[0].color = sf::Color::Red;
                    m_shape[2].color = sf::Color::Blue;

                    fe::inputManager::get().add<testEntity>(fe::input<sf::Keyboard::Key, testEntity*>(true, true, sf::Keyboard::A, fe::function<void(testEntity*)>(this, &testEntity::moveLeft)));
                    fe::inputManager::get().add<testEntity>(fe::input<sf::Keyboard::Key, testEntity*>(true, true, sf::Keyboard::D, fe::function<void(testEntity*)>(this, &testEntity::moveRight)));
                }

            void update(float deltaTime)
                {
                    m_shape[0].position += m_speed.convertToSfVec2() * deltaTime;
                    m_shape[1].position += m_speed.convertToSfVec2() * deltaTime;
                    m_shape[2].position += m_speed.convertToSfVec2() * deltaTime;
                    m_shape[3].position += m_speed.convertToSfVec2() * deltaTime;

                    m_speed = fe::Vector2d();
                }

            void draw(sf::RenderWindow &app)
                {
                    app.draw(m_shape);
                }
    };

class gameState : public fe::baseGameState
    {
        private:
        public:
            void init()
                {
                    addEntity<testEntity>();
                }
    };

int main()
    {
        fe::engine engine;
        engine.startUp();

        gameState game;
        engine.queueState(&game);

        fe::function<void(fe::memoryManager*)> a(&fe::memoryManager::get(), &fe::memoryManager::printDebugInformation);
        fe::inputManager::get().add(fe::input<sf::Keyboard::Key, fe::memoryManager*>(false, true, sf::Keyboard::Tilde, a));
        engine.run();

        engine.shutDown();
        return 0;
    }