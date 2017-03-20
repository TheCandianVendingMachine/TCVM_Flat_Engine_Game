// gameState.hpp
// the main state that updates all entities
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include "../entities/paddle.hpp"

class gameState : public fe::baseGameState
    {
        public:
            void init()
                {
                    addEntity<paddle>(fe::Vector2d(40, 0));
                }
    };