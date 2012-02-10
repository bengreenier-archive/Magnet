/*
#ifndef CIRCLE_H
#define CIRCLE_H

#include <Box2D/Box2D.h>

#include "PhysShape.h"

class Circle : public PhysShape //! A PhysShape, that is a circle. Used in World.
{
    public:

        Circle(int radius,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< Standard Constructor
        Circle(int radius,b2Vec2 tForce,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< ApplyForce Constructor
        Circle(int radius,bool staticc,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< Static Constructor
        Circle(int radius,b2Vec2 radialgrav,int radialdist=10,bool staticc=true,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< radial grav Constructor
        /** generic public functions */
        //virtual void Create(b2World* p_world); //!< Does all the work of creating both the sfml and the b2d shape.

          /** Default destructor */
        //~Circle();//!< Deconstructor

        /** Access m_Radius
         * \return The current value of m_Radius
         */
        //int Get_Radius() { return m_Radius; } //!< Access the radius

        /** Set m_Radius
         * \param val New value to set
         */
        //void Set_Radius(int val) { m_Radius = val; } //!< Set the radius
/*

    protected:
    private:
        int m_Radius; //!< Member variable "m_Radius"
};

#endif // CIRCLE_H
*/
