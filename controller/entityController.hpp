// entityController.hpp
// allows an entity to be controlled by a method
#pragma once
class paddle;
class entityController
    {
        protected:
            paddle *m_controlling;
            bool m_enabled;

        public:
            entityController(paddle *paddle);

            virtual void enable(bool value);
            virtual void update() {}

    };