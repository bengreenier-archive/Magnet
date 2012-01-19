#ifndef PHYSSHAPE_H
#define PHYSSHAPE_H

#include <iostream>
#include <Box2D/Box2D.h>

#include "ref.h"
#include "../Material/Material.h"
#include "../WorldStandards.h"
#include "../SelectiveCollision.h"

//this class is legit useless. other then all PhysShapes inherit it.

class PhysShape //! The base class for each PhysShape, Like Circle,Line,Etc.
{
    public:

        /*overide these in each PhysShape*/
        virtual void Destroy() { std::cout<<"[PhysShape] [Destroy] Not overidden.\n"; } //!< A virtual Destroy function, that should get overridden.
        virtual void Create() { std::cout<<"[PhysShape] [Create] Not overidden.\n"; } //!< A virtual Create function, that should get overridden.
        virtual void Update() { std::cout<<"[PhysShape] [Update] Not overidden.\n"; } //!< A virtual Update function, that should get overridden.
        void ApplyForce(b2Vec2 force) {std::cout<<"gotin\n"; Get_Body()->ApplyForce(force,Get_Body()->GetWorldCenter()); std::cout<<"gotit\n"; } //!< Apply a force to a body.

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
};

#endif // PHYSSHAPE_H
