/*#ifndef PROJECTILE_H
#define PROJECTILE_H


#include "PhysShape.h"

class Projectile : public PhysShape
{
    public:

        Projectile(sf::Vector2f pos,b2Vec2 tForce=b2Vec2(0,50),Material* mat=new Material(MatType::Default),float degangle=0);//!< Default Constructor

        ~Projectile();//!< Default Deconstructor

                /* generic public functions */
        //virtual void Create(b2World* p_world); //!< Create the b2d/sfml Rectangle objects.


       // void Set_Bullet(bool val){ m_isbullet = val; }//!< True if is a bullet (default) false otherwise
        //bool Get_Bullet(){ return m_isbullet; }//!< Returning if is bullet

        //int Get_Width() { return m_Width; }

        /** Set m_Width
         * \param val New value to set
         */
        //void Set_Width(int val) { m_Width = val; }

        /** Access m_Height
         * \return The current value of m_Height
         */
       // int Get_Height() { return m_Height; }

        /** Set m_Height
         * \param val New value to set
         */
     /*   void Set_Height(int val) { m_Height = val; }

        void Set_Force(b2Vec2 val) { m_force = val; }

        b2Vec2 Get_Force() { return m_force; }

    protected:
    private:
        bool m_isbullet;
        int m_Width; //!< Member variable "m_Width"
        int m_Height; //!< Member variable "m_Height"
        b2Vec2 m_force;//!< Member variable "m_froce
};

#endif // PROJECTILE_H
*/
