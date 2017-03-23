// ball.hpp
// ball for the pong game
#pragma once
#include <fe/entity/baseEntity.hpp>
#include <fe/collision/colliders.hpp>

class ball : public fe::baseEntity
    {
        private:
            fe::AABB<ball> m_bounds;
            fe::Vector2d m_speed;

            void onCollision(const fe::collider *collision);

        public:
            ball(fe::Vector2d position);
            void update(float deltaTime);
            const fe::collider &getCollider();
    };