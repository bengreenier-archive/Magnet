#include "Material.h"

Material::Material(MatType::Type in)
{
    //ctor

    //switch types, and call their config methods.
    switch(in)
    {
        case MatType::Heavy:{m_Heavy();}break;
        case MatType::Light:{m_Light();}break;
        case MatType::Floor:{m_Floor();}break;
        default:{m_Default();}break;
    }
}

Material::~Material()
{
    //dtor
}

void Material::m_Default()
{
//creates a default material.
m_density = 1.0f;
m_restitution = 0.002f;
m_friction = 0.3f;
m_color = sf::Color(255,0,0);

}

void Material::m_Heavy()
{
//creates a Heavy material
m_density = 2.0f;
m_restitution = 0.00002f;
m_friction = 0.6f;
m_color = sf::Color(121,10,250);

}

void Material::m_Light()
{
//creates a light matherial
m_density = 0.5f;
m_restitution = 0.2f;
m_friction = 0.003f;
m_color = sf::Color(21,40,250);

}

void Material::m_Floor()
{
    m_density = 2.0f;
    m_restitution = 0.00002f;
    m_friction = 0.6f;
    m_color = sf::Color(21,0,255);
}

float Material::GetDensity()
{
    return m_density;
}

float Material::GetRestitution()
{
    return m_restitution;
}

float Material::GetFriction()
{
    return m_friction;
}


sf::Color Material::GetColor()
{
    return m_color;
}
