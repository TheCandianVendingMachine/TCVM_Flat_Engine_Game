// Flat Engine Game
// A game that will be made alongside the engine. Meant to reduce scope of the engine
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fe/engine.hpp>
#include <fe/subsystems/gameState/gameState.hpp>

class testEntity : public fe::baseEntity
    {
        private:
            fe::Vector2d m_speed;

            void moveRight() { m_speed.x = 200.f; }
            void moveLeft() { m_speed.x = -200.f; }

        public:
            testEntity(fe::Vector2d position)
                {
                    m_verticies[0].position = sf::Vector2f(0, 0);
                    m_verticies[1].position = sf::Vector2f(20, 0);
                    m_verticies[2].position = sf::Vector2f(20, 20);
                    m_verticies[3].position = sf::Vector2f(0, 20);

                    m_verticies[0].color = sf::Color::Red;
                    m_verticies[2].color = sf::Color::Blue;

                    setPosition(position);

                    //fe::inputManager::get().add<testEntity>(fe::input<sf::Keyboard::Key, testEntity*>(true, true, sf::Keyboard::A, fe::function<void(testEntity*)>(this, &testEntity::moveLeft)));
                    //fe::inputManager::get().add<testEntity>(fe::input<sf::Keyboard::Key, testEntity*>(true, true, sf::Keyboard::D, fe::function<void(testEntity*)>(this, &testEntity::moveRight)));
                }

            void update(float deltaTime)
                {
                    move(m_speed * deltaTime);
                    m_speed = fe::Vector2d();
                }
    };

class gameState : public fe::baseGameState
    {
        private:
        public:
            void init()
                {
                    for (int i = 0; i < 64; ++i)
                        {
                            for (int j = 0; j < 36; ++j) 
                                {
                                    addEntity<testEntity>(fe::Vector2d((i * 20) + 1, (j * 20) + 1));
                                }
                        }
                }
    };

fe::engine engine;

void debug()
    {
        fe::memoryManager::get().printDebugInformation();
        std::cout << "\nFPS: " << engine.getFPS() << "\n\n";
    }

int main()
    {
        engine.startUp();

        gameState game;
        engine.queueState(&game);

        fe::inputManager::get().add(fe::input<sf::Keyboard::Key>(false, true, sf::Keyboard::Tilde, fe::function<void()>(debug)));
        engine.run();

        engine.shutDown();
        return 0;
    }