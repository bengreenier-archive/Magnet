#ifndef WORLD_H
#define WORLD_H

#include <BOX2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <list>

#include "../Game/Renderer.h"

class World
{
    public:
        World();
        b2World* Access(); //World::access()->  to work with. looks nice.
        sf::RenderWindow* RenderAccess();//just calls renderer cmd, but is "pretty" to have here.

        sf::Color B2SFColor(const b2Color &color, int alpha = 255); //convert a b2color to sfml

    protected:
    private:
        b2World* m_world1; //our first/potentially-only physics world.
        std::list <b2Body*> b2PhysicsObjects; //a list of all b2 pointers. push_front this.
};

#endif // WORLD_H
