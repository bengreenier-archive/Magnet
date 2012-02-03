#ifndef PHYSSHAPE_H
#define PHYSSHAPE_H

#include <iostream>
#include <Box2D/Box2D.h>

//things shapes use
#include "WorldShapes.h"
#include "../Material/Material.h"
#include "../WorldStandards.h"
#include "../SelectiveCollision.h"
#include "../../Game/Renderer.h"

class PhysShape //! The base class for each PhysShape, Like Circle,Line,Etc.
{
    public:

        /*overide these in each PhysShape*/
        virtual void Destroy(b2World* p_world) {

            Renderer::RemoveLink(Get_Shape());
            p_world->DestroyBody(Get_Body());
        if (WorldStandards::debug)
        std::cout << "[SFML/Box2D] Removed Shape.\n";


        } //!< A virtual Destroy function, that should get overridden.
        virtual void Create(b2World* p_world) { std::cout<<"[PhysShape] [Create] Not overidden.\n"; } //!< A virtual Create function, that should get overridden.
        virtual void Update() { Get_Shape()->SetPosition(Get_Position()); Get_Shape()->Rotate(Get_Angle()); } //!< A virtual Update function, that should get overridden.

        virtual void Hide() { Renderer::RemoveLink(Get_Shape()); }

        void ApplyForce(b2Vec2 force) { Get_Body()->ApplyForce(force,Get_Body()->GetWorldCenter()); } //!< Apply a force to a body.

        /** Access m_Mat
         * \return The current value of m_Mat
         */
        Material* Get_Mat() { return m_Mat; }

        /** Set m_Mat
         * \param val New value to set
         */
        void Set_Mat(Material* val) { m_Mat = val; }

        /** Access m_ShapeType
         * \return The current value of m_ShapeType
         */
        WorldShapes::Type Get_ShapeType() { return m_ShapeType; }

        /** Set m_ShapeType
         * \param val New value to set
         */
        void Set_ShapeType(WorldShapes::Type val) { m_ShapeType = val; }

        /** Access m_Position
         * \return The current value of m_Position
         */
        sf::Vector2f Get_Position() { return m_Position; }

        /** Set m_Position
         * \param val New value to set
         */
        void Set_Position(sf::Vector2f val) { m_Position = val; }

        /** Access m_Angle
         * \return The current value of m_Angle
         */
        float Get_Angle() { return m_Angle; }

        /** Set m_Angle
         * \param val New value to set
         */
        void Set_Angle(float val) { m_Angle = val; }

        /** Access m_Static
         * \return The current value of m_Static
         */
        bool Get_Static() { return m_Static; }

        /** Set m_Static
         * \param val New value to set
         */
        void Set_Static(bool val) { m_Static = val; }

                /** Access m_Shape
         * \return The current value of m_Shape
         */
        sf::Shape* Get_Shape() { return m_Shape; }

        /** Set m_Shape
         * \param val New value to set
         */
        void Set_Shape(sf::Shape* val) { m_Shape = val; }

        /** Access m_Body
         * \return The current value of m_Body
         */
        b2Body* Get_Body() { return m_Body; }

        /** Set m_Body
         * \param val New value to set
         */
        void Set_Body(b2Body* val) { m_Body = val; }

        SelectiveCollision* Get_AdjustCollision() {return m_AdjustCollision; }
        void Set_AdjustCollision(SelectiveCollision* val){ m_AdjustCollision = val; }

        b2World* Get_C_World() { return m_created_with_world;}
        void Set_C_World(b2World* in){m_created_with_world=in;}

        bool HasRadialGravity() { if ((r_grav == b2Vec2(0,0))||(r_grav_dist<=0)){return false; }else{ return true;} }
        void Set_Radial_Gravity(b2Vec2 in){ r_grav = b2Vec2(in.x*WorldStandards::ppm,in.y*WorldStandards::ppm);}
        b2Vec2 Get_Radial_Gravity(){return r_grav;}

        void Set_Radial_Gravity_Distance(int in ){r_grav_dist = in*WorldStandards::ppm;}
        int Get_Radial_Gravity_Distance(){return r_grav_dist;}


        void Set_CreateWithForce(bool in){m_createwithforce = in;}
        void Set_CreateWithForce_Force(b2Vec2 tForce){m_createwithforce_force = tForce; }
        bool Get_CreateWithForce(){return m_createwithforce;}
        b2Vec2 Get_CreateWithForce_Force(){return m_createwithforce_force;}

        void pullorpush_val_set(int val){pop_val = val; }
        int pullorpush_val(){return pop_val; }

    protected:
    private:
        sf::Shape*          m_Shape;    //!< Member variable "m_Shape"
        b2Body*             m_Body;     //!< Member variable "m_Rect"
        Material*           m_Mat;      //!< Member variable "m_Mat"
        WorldShapes::Type   m_ShapeType;//!< Member variable "m_ShapeType"
        sf::Vector2f        m_Position; //!< Member variable "m_Position"
        float               m_Angle;    //!< Member variable "m_Angle"
        bool                m_Static;   //!< Member variable "m_Static"
        SelectiveCollision* m_AdjustCollision;
        b2World* m_created_with_world;
        b2Vec2 r_grav;//!< gravity that this shape applies radially
        int r_grav_dist;//!< how close a shape needs to be to be effected
        bool m_createwithforce;
        b2Vec2 m_createwithforce_force;
        int pop_val;


};

#endif // PHYSSHAPE_H
