// gameState.hpp
// the main state that updates all entities
#pragma once
#include <fe/subsystems/gameState/gameState.hpp>
#include <fe/engine.hpp>
#include "../entities/paddle.hpp"
#include "../entities/ball.hpp"

class gameState : public fe::baseGameState
    {
        public:
            void init()
                {
                    addEntity<paddle>(fe::Vector2d(40, 0));
                    auto a = fe::engine::getWindowSize();
                    addEntity<ball>(a / 2.f);
                }
    };