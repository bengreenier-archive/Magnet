#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "PhysShape.h"

class Triangle: public PhysShape
{
    public:
        /** Default constructor */
        Triangle(int size,sf::Vector2f Globalpos,b2Vec2 tForce,Material* mat=new Material(MatType::Default),float degangle = 0);
        Triangle(int size,sf::Vector2f Globalpos,Material* mat=new Material(MatType::Default),float degangle = 0);
        Triangle(int size,sf::Vector2f Globalpos,bool staticc,Material* mat=new Material(MatType::Default),float degangle = 0);
        /** Default destructor */
        ~Triangle();

        /** Overidden Functions*/
        virtual void Create();
        virtual void Destroy();
        virtual void Update();

    protected:
    private:
        int m_size;
};

#endif // TRIANGLE_H
