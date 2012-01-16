#ifndef CIRCLE_H
#define CIRCLE_H


#include "PhysShape.h"

class Circle : public PhysShape
{
    public:
        /** Default constructor */
        Circle(int radius,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0);
        Circle(int radius,b2Vec2 tForce,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0);
        Circle(int radius,bool staticc,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0);

        /** generic public functions */
        virtual void Create();
        virtual void Destroy();
        virtual void Update();

        /** Default destructor */
        ~Circle();

        /** Access m_Radius
         * \return The current value of m_Radius
         */
        int Get_Radius() { return m_Radius; }

        /** Set m_Radius
         * \param val New value to set
         */
        void Set_Radius(int val) { m_Radius = val; }


    protected:
    private:
        int m_Radius; //!< Member variable "m_Radius"
};

#endif // CIRCLE_H
