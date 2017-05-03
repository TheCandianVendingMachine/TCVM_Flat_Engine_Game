#include "playerController.hpp"
#include "../entities/paddle.hpp"
#include <fe/subsystems/input/inputManager.hpp>
#include <functional>

playerController::playerController(paddle *paddleEnt, int playerNum) : entityController(paddleEnt)
    {
        fe::input up(std::bind(&paddle::moveUp, m_controlling), true);
        fe::input down(std::bind(&paddle::moveDown, m_controlling), true);

        sf::Keyboard::Key moveUp;
        sf::Keyboard::Key moveDown;

        switch (playerNum)
            {
                case 0:
                    moveUp = sf::Keyboard::W;
                    moveDown = sf::Keyboard::S;
                    break;
                case 1:
                    moveUp = sf::Keyboard::Up;
                    moveDown = sf::Keyboard::Down;
                    break;
                default:
                    break;
            }

        m_upHandle = fe::inputManager::get().add(moveUp, up);
        m_downHandle = fe::inputManager::get().add(moveDown, down);
    }

void playerController::enable(bool value)
    {
        m_enabled = value;
        fe::inputManager::get().setActive(m_upHandle, value);
        fe::inputManager::get().setActive(m_downHandle, value);
    }

playerController::~playerController()
    {
        fe::inputManager::get().removeObject(m_upHandle);
        fe::inputManager::get().removeObject(m_downHandle);
    }
