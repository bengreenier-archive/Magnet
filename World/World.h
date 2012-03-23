/*
#ifndef WORLD_H
#define WORLD_H

#include <BOX2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Game/Renderer.h"

#include "Entity.h"
#include "EntityDimensions.h"

//Other World-ly includes
#include "WorldStandards.h"
#include "Material/Material.h"
/*
#include "Stats/WorldStats.h"

class World //! The world object. controls all physics and world-ly things. :)
{
    public:
        World(int constraint=500,b2Vec2 m_grav=b2Vec2(0,10),float timestep = (1.0f/40.0f),int velocityit = 8, int positionit = 3,int maxbodies = 800, Material* defaultmaterial = new Material(MatType::Default)); //!< Default Constructor

        b2World* CurrentB2World();//!< Returns a pointer to the current world.

        void Step();//!< IMPORTANT: Does the stepping over the CurrentWorld().

        void SetTimestep(float in);//!< Adjust the timestep
        float GetTimestep(); //!< Get the timestep
        void SetGravity(b2Vec2 in);
        b2Vec2 GetGravity();

        void AwakenAll();//!< Awaken all b2bodies.

        void AddShape(Entity* in);

        int uuid;//!< WorldManager sets this and its different for each World
        Material* CurrentMaterial(); //!< Points to the current material
        void SetCurrentMaterial(Material* in);//!< Changes the current material


        void Unload();//!< Unloads the World. UnLinking Renderer, then deleting whatever it can
        void Hide();//!< De Renderer's the Worlds stuff.

    protected:
    private:
        float32 m_timeStep;
        int32 m_velocityIterations;
        int32 m_positionIterations;
        bool m_hooked;
        b2Vec2 m_MouseVector1;
        b2Vec2 m_MouseVector2;
        b2Vec2 m_MouseVector;

        b2Vec2 m_grav;

        WorldStats* Stat;


        int maxPhysicsBodies;
        //our array of world constrainst. set in constructor.
        sf::Vector2i worldConstraint[2];

        Material* m_curMat;

        b2World* m_selected;// a pointer to the selected world.
        b2World* m_world1; //our first/potentially-only physics world.

        std::vector<Entity*> Objects,StaticObjects;

        std::vector <Entity*> Queue;

        //processes the above.
        void ProcessQueue(std::vector<Entity*>* Q,std::string fx);



};

#endif // WORLD_H
*/

