#ifndef WORLD_H
#define WORLD_H

#include <BOX2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Magnet.h"
#include "WorldStandards.h"

class World
{
    public:
        World();

        static World* Access(); //World::access()->  to work with. looks nice.
        static void Init();

        sf::Color B2SFColor(const b2Color &color, int alpha = 255); //convert a b2color to sfml

        void AddBox(int x,int y,int x2,int y2,sf::Vector2f pos=sf::Vector2f(0,0));
        void AddStaticBox(int x,int y,int x2,int y2,sf::Vector2f pos=sf::Vector2f(0,0));

        b2World* CurrentWorld();//returns current world.

        void Step();//sets over world once.

        static void HookHelper();

    protected:
    private:
        // Prepare for simulation. Typically we use a time step of 1/60 of a
        // second (60Hz) and 10 iterations. This provides a high quality simulation
        // in most game scenarios.
        float32 m_timeStep;
        int32 m_velocityIterations;
        int32 m_positionIterations;
        bool m_hooked;

        void ActivateHook();//hooks the step for this world.

        static World* m_ptr;

        b2World* m_selected;// a pointer to the selected world.
        b2World* m_world1; //our first/potentially-only physics world.
        std::vector <b2Body*> b2PhysicsObjects; //a list of all b2 pointers. push_front this.
        std::vector <sf::Drawable*> sfPhysicsObjects; //a list of all sf pointers. push_front this.

        std::vector <World*> worldList; //so that we can hook world steps...?
};

#endif // WORLD_H
