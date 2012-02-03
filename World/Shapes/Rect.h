#ifndef RECT_H
#define RECT_H

#include "PhysShape.h"

class Rect : public PhysShape //! The Rectangle PhysShape. Used in World.
{
    public:

        Rect(int width,int height,b2Vec2 tForce,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< Force Constructor
        Rect(int width,int height,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< Default Constructor
        Rect(int width,int height,bool staticc,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< Static Constuctor
        Rect(int width,int height,b2Vec2 radialgrav,int radialdist=10,bool staticc=true,sf::Vector2f pos = sf::Vector2f(0,0),Material* mat=new Material(MatType::Default),float degangle = 0); //!< Static Constuctor

        /* generic public functions */
        virtual void Create(b2World* p_world); //!< Create the b2d/sfml Rectangle objects.


        ~Rect();//!< Default Deconstructor

        /** Access m_Width
         * \return The current value of m_Width
         */
        int Get_Width() { return m_Width; }

        /** Set m_Width
         * \param val New value to set
         */
        void Set_Width(int val) { m_Width = val; }

        /** Access m_Height
         * \return The current value of m_Height
         */
        int Get_Height() { return m_Height; }

        /** Set m_Height
         * \param val New value to set
         */
        void Set_Height(int val) { m_Height = val; }

    protected:
    private:
        int m_Width; //!< Member variable "m_Width"
        int m_Height; //!< Member variable "m_Height"

};

#endif // RECT_H
