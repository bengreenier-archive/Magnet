#ifndef WORLD_H
#define WORLD_H

#include <BOX2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Magnet.h"
#include "../FileActions/Xml/xml_include.h"

//Other World-ly includes
#include "WorldStandards.h"
#include "Material/Material.h"
#include "Stats/WorldStats.h"

//PhysShape Includes
#include "Shapes/PhysShape.h"
#include "Shapes/Circle.h"
#include "Shapes/Rect.h"
#include "Shapes/Line.h"
#include "Shapes/Triangle.h"

//Network Mats
#include "Material/Network/NetMaterialRegistry.h"


class World //! The world object. controls all physics and world-ly things. :)
{
    public:
        World(); //!< Default Constructor

        static World* Access(); //!< Access the world object.
        static void Init(); //!< Initialize the world object. (calls constructor, setting pointer along the way)

        sf::Color B2SFColor(const b2Color &color, int alpha = 255); //!< useless function that converts colors.

        b2World* CurrentWorld();//!< Returns a pointer to the current world.

        void Step();//!< IMPORTANT: Does the stepping over the CurrentWorld().

        void SetTimestep(float in);//!< Adjust the timestep
        float GetTimestep(); //!< Get the timestep

        static void HookHelper(); //!< Called on Hook::Frame
        static void Hook_Setup(); //!< Setup World.


        static bool Event_Click(sf::Event evt); //!< Called on Event_Click
        static bool Event_KeyPresed(sf::Event evt); //!< Called on Event_KeyPressed
        static bool Event_MouseMove(sf::Event evt); //!< Event_MouseMove

        //static binders for material-current changing
        static void Default(sf::Event evt); //!< Binder for current material changing.
        static void Heavy(sf::Event evt);//!< Binder for current material changing.
        static void Light(sf::Event evt);//!< Binder for current material changing.
        static void Rubber(sf::Event evt);//!< Binder for current material changing.
        static void Wood(sf::Event evt);//!< Binder for current material changing.

        static void AddShape(PhysShape* shape); //!< Add a PhysShape to the world

    protected:
    private:
        float32 m_timeStep;
        int32 m_velocityIterations;
        int32 m_positionIterations;
        bool m_hooked;
        b2Vec2 m_MouseVector1;
        b2Vec2 m_MouseVector2;


        static World* m_ptr;

        NetMaterial::Registry* m_matreg;//the netregistry to materials

        WorldStats* Stat;

        Material* CurrentMaterial(); //!< Points to the current material

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

};

#endif // WORLD_H
