#include "playerController.hpp"
#include "../entities/paddle.hpp"
#include <fe/subsystems/input/inputManager.hpp>
#include <functional>

playerController::playerController(paddle *paddleEnt, int playerNum) : entityController(paddleEnt)
    {
        fe::input<sf::Keyboard::Key> down;
        fe::input<sf::Keyboard::Key> up;

        switch (playerNum)
            {
                case 0:
                    down = fe::input<sf::Keyboard::Key>(true, true, sf::Keyboard::S, std::bind(&paddle::moveDown, m_controlling));
                    up = fe::input<sf::Keyboard::Key>(true, true, sf::Keyboard::W, std::bind(&paddle::moveUp, m_controlling));
                    
                    m_moveUp = "upP1";
                    m_moveDown = "downP1";
                    break;
                case 1:
                    down = fe::input<sf::Keyboard::Key>(true, true, sf::Keyboard::Down, std::bind(&paddle::moveDown, m_controlling));
                    up = fe::input<sf::Keyboard::Key>(true, true, sf::Keyboard::Up, std::bind(&paddle::moveUp, m_controlling));
                    
                    m_moveUp = "upP2";
                    m_moveDown = "downP2";
                    break;
                default:
                    break;
            }

        fe::inputManager::get().add(m_moveUp.c_str(), up);
        fe::inputManager::get().add(m_moveDown.c_str(), down);
    }

void playerController::enable(bool value)
    {
        m_enabled = value;
        fe::inputManager::get().setActive(m_moveUp.c_str(), value);
        fe::inputManager::get().setActive(m_moveDown.c_str(), value);
    }
