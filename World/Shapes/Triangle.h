#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "PhysShape.h"

class Triangle: public PhysShape
{
    public:
        /** Default constructor */
        Triangle(sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos,b2Vec2 tForce,Material* mat=new Material(MatType::Default),float degangle = 0);
        Triangle(sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos,Material* mat=new Material(MatType::Default),float degangle = 0);
        Triangle(sf::Vector2f pos1,sf::Vector2f pos2,sf::Vector2f pos3,sf::Vector2f Globalpos,bool staticc,Material* mat=new Material(MatType::Default),float degangle = 0);
        /** Default destructor */
        ~Triangle();

        /** Overidden Functions*/
        virtual void Create();
        virtual void Destroy();
        virtual void Update();

    protected:
    private:
    sf::Vector2f pos1;
    sf::Vector2f pos2;
    sf::Vector2f pos3;
};

#endif // TRIANGLE_H
