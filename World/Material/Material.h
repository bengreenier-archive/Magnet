#ifndef MATERIAL_H
#define MATERIAL_H


//the base material class, most materials should be able to be this.
//the only reason for a derived class would be a material like door that has a .click member function,etc.

//SHOULD HANDLE COLORS/TEXTURES/IMAGES EVENTUALLY TOO.
#include <SFML/Graphics.hpp>

namespace MatType{

    enum Type{
        Default,
        Heavy,
        Light,
        Floor,
        Rubber,
        Wood
    };

}

class Material
{
    public:
        Material(MatType::Type in=MatType::Default);
        ~Material();
        float GetDensity();
        float GetRestitution();
        float GetFriction();
        sf::Color GetColor();
    protected:
    private:
        float m_density;
        float m_restitution;
        float m_friction;
        sf::Color m_color;

        //these set things up for each type. each type has a function here.
        void m_Default();
        void m_Heavy();
        void m_Light();
        void m_Floor();
        void m_Rubber();
        void m_Wood();

};



#endif // BASE_H
