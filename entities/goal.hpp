// goal.hpp
// the goal. If the ball enters this, the game will reset
#pragma once
#include <fe/entity/baseEntity.hpp>
#include <fe/subsystems/graphic/sceneGraph.hpp>

class goal : public fe::baseEntity
    {
        private:
            fe::Handle m_ball;
            int m_goalSide;

        public:
            goal(fe::Handle ball, int goal, fe::Vector2d position);

            void onAdd(fe::baseGameState &state);
            void update(float deltaTime);
    };