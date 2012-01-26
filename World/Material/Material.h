#ifndef MATERIAL_H
#define MATERIAL_H


//the base material class, most materials should be able to be this.
//the only reason for a derived class would be a material like door that has a .click member function,etc.

//SHOULD HANDLE COLORS/TEXTURES/IMAGES EVENTUALLY TOO.
#include <SFML/Graphics.hpp>
#include <string>

namespace MatType{ //! The List of all materials any PhysShape can have.

    enum Type{
        Default,
        Heavy,
        Light,
        Floor,
        Rubber,
        Wood
    };

}

class Material //! The material class, defining a material that a PhysShape can be.
{
    public:
        Material(MatType::Type in=MatType::Default); //!< Default Constructor
        Material(float density,float rest,float fric,sf::Color col,std::string name);//!< Long Contructor
        ~Material(); //!< Default Deconstructor
        float GetDensity(); //!< Get material instance's density
        float GetRestitution(); //!< Get material instance's restitution
        float GetFriction(); //!< Get material instance's friction
        sf::Color GetColor(); //!< Get material instance's color
        std::string GetName();//!< Get materials name (not always defined)
    protected:
    private:
        float m_density;
        float m_restitution;
        float m_friction;
        sf::Color m_color;
        std::string m_name;//!< Not always needed/used.

        //these set things up for each type. each type has a function here.
        void m_Default();
        void m_Heavy();
        void m_Light();
        void m_Floor();
        void m_Rubber();
        void m_Wood();

};



#endif // BASE_H
