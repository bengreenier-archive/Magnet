#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "PhysShape.h"

class Triangle: public PhysShape
{
    public:

        Triangle(int size,sf::Vector2f Globalpos,b2Vec2 tForce,Material* mat=new Material(MatType::Default),float degangle = 0); //!< Force Constructor
        Triangle(int size,sf::Vector2f Globalpos,Material* mat=new Material(MatType::Default),float degangle = 0); //!< Default Constructor
        Triangle(int size,sf::Vector2f Globalpos,bool staticc,Material* mat=new Material(MatType::Default),float degangle = 0); //!< Static Constructor

        ~Triangle(); //!< Default Deconstructor


        virtual void Create(); //!< Create the triangle in both physics engine and render engine.
        virtual void Destroy(); //!< Remove the triangle in both physics engine and render engine.
        virtual void Update(); //!< Updaye the triangle from set values, so Set_Position before calling this.

    protected:
    private:
        int m_size;
};

#endif // TRIANGLE_H
