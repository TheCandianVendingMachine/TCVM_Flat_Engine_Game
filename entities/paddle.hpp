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
            fe::Vector2d m_velocity;

            const float m_speed;

            void moveUp() { m_velocity.y = -m_speed; }
            void moveDown() { m_velocity.y = m_speed; }

        public:
            paddle(fe::Vector2d position);
            void onAdd(fe::baseGameState &state);

            void update(float deltaTime);

    };