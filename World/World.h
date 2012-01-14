#ifndef WORLD_H
#define WORLD_H

#include <BOX2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Magnet.h"

//Other World-ly includes
#include "WorldStandards.h"
#include "Material/Material.h"
#include "Stats/WorldStats.h"

//PhysShape Includes
#include "Shapes/PhysShape.h"
#include "Shapes/Circle.h"
#include "Shapes/Rect.h"

class World
{
    public:
        World();

        static World* Access(); //World::access()->  to work with. looks nice.
        static void Init();

        sf::Color B2SFColor(const b2Color &color, int alpha = 255); //convert a b2color to sfml

        b2World* CurrentWorld();//returns current world.

        void Step();//steps over world once.

        void SetTimestep(float in);//set the world speed.
        float GetTimestep();

        static void HookHelper();
        static void Hook_Setup();

        static void ClickCircle(sf::Event evt);
        static void ClickBox(sf::Event evt);

        //static binders for material-current changing
        static void Default(sf::Event evt);
        static void Heavy(sf::Event evt);
        static void Light(sf::Event evt);
        static void Rubber(sf::Event evt);
        static void Wood(sf::Event evt);

    protected:
    private:
        float32 m_timeStep;
        int32 m_velocityIterations;
        int32 m_positionIterations;
        bool m_hooked;

        static World* m_ptr;

        WorldStats* Stat;

        Material* CurrentMaterial();

        int maxPhysicsBodies;
        //our array of world constrainst. set in constructor.
        sf::Vector2i worldConstraint[2];

        Material* m_curMat;

        b2World* m_selected;// a pointer to the selected world.
        b2World* m_world1; //our first/potentially-only physics world.

        std::vector<PhysShape*> Objects;

        std::vector <PhysShape*> Queue;

        //processes the above.
        void ProcessQueue(std::vector<PhysShape*>* Q,std::string fx);
        int GetObjectIndex(PhysShape* in);
        int GetIndex(vector<PhysShape*>* in,PhysShape* sh);
};

#endif // WORLD_H
