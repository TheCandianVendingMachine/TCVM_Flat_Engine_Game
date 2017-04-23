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
                    m_moveUp = "upP1";
                    m_moveDown = "downP1";

                    fe::inputManager::get().add(sf::Keyboard::W, up);
                    fe::inputManager::get().add(sf::Keyboard::S, down);
                    break;
                case 1:
                    fe::inputManager::get().add(sf::Keyboard::Up, up);
                    fe::inputManager::get().add(sf::Keyboard::Down, down);
                    break;
                default:
                    break;
            }
    }

void playerController::enable(bool value)
    {
        m_enabled = value;
        fe::inputManager::get().setActive(sf::Keyboard::Up, value);
        fe::inputManager::get().setActive(sf::Keyboard::Down, value);

        fe::inputManager::get().setActive(sf::Keyboard::W, value);
        fe::inputManager::get().setActive(sf::Keyboard::S, value);
    }
