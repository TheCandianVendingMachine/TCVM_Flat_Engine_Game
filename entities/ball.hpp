// ball.hpp
// ball for the pong game
#pragma once
#include <fe/entity/baseEntity.hpp>
#include <fe/collision/colliders.hpp>

class ball : public fe::baseEntity
    {
        private:
            fe::Vector2d m_velocity;

            const float m_speed;

        public:
            ball(fe::Vector2d position);
            void onAdd(fe::baseGameState &state);

            void update(float deltaTime);

            void collision(const fe::collider &collision);
    };