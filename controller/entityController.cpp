#include "entityController.hpp"

entityController::entityController(paddle *paddle) : m_controlling(paddle), m_enabled(true)
    {
    }

void entityController::enable(bool value)
    {
        m_enabled = value;
    }
