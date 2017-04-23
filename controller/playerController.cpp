#include "playerController.hpp"
#include "../entities/paddle.hpp"
#include <fe/subsystems/input/inputManager.hpp>
#include <functional>

playerController::playerController(paddle *paddleEnt, int playerNum) : entityController(paddleEnt)
    {
        fe::input up(std::bind(&paddle::moveUp, m_controlling), true);
        fe::input down(std::bind(&paddle::moveDown, m_controlling), true);

        switch (playerNum)
            {
                case 0:
                    m_moveUp = sf::Keyboard::W;
                    m_moveDown = sf::Keyboard::S;
                    break;
                case 1:
                    m_moveUp = sf::Keyboard::Up;
                    m_moveDown = sf::Keyboard::Down;
                    break;
                default:
                    break;
            }

        fe::inputManager::get().add(m_moveUp, up);
        fe::inputManager::get().add(m_moveDown, down);
    }

void playerController::enable(bool value)
    {
        m_enabled = value;
        fe::inputManager::get().setActive(m_moveUp, value);
        fe::inputManager::get().setActive(m_moveDown, value);
    }
