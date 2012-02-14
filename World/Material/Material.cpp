#include "Material.h"
#include "../../Game/Resource.h"

Material::Material(MatType::Type in)
{
    //ctor
    m_name = "";
    m_useImage=false;
    m_useText=false;
    //switch types, and call their config methods.
    switch(in)
    {
        case MatType::Heavy:{m_Heavy();}break;
        case MatType::Light:{m_Light();}break;
        case MatType::Floor:{m_Floor();}break;
        case MatType::Rubber:{m_Rubber();}break;
        case MatType::Wood:{m_Wood();}break;
        case MatType::Ground:{m_Ground_Img();}break;
        default:{m_Default();}break;
    }
}

Material::Material(float density,float rest,float fric,sf::Color col,std::string name)
{
    m_density = density;
    m_friction = fric;
    m_restitution = rest;
    m_color = col;
    m_name = name;
    m_useImage=false;
    m_useText=false;
}


Material::Material(float density,float rest,float fric,std::string imagepath)
{
    m_density = density;
    m_friction = fric;
    m_restitution = rest;
    m_color = sf::Color(0,0,0);
    m_name = imagepath;


    m_image = sf::Texture();
    m_image.Update(Resource::GetImage(imagepath));
    m_useImage=true;
    m_useText=false;

}

Material::Material(float density,float rest,float fric,std::string text,std::string fontpath)
{
    m_density = density;
    m_friction = fric;
    m_restitution = rest;
    m_color = sf::Color(0,0,0);
    m_name = text;



    m_font = Resource::GetFont(fontpath);
    m_text = sf::Text(text,m_font);
    m_useImage=false;
    m_useText=true;

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
m_name = "Default";

}

void Material::m_Heavy()
{
//creates a Heavy material
m_density = 2.0f;
m_restitution = 0.00002f;
m_friction = 0.6f;
m_color = sf::Color(121,10,250);
m_name = "Heavy";

}

void Material::m_Light()
{
//creates a light matherial
m_density = 0.5f;
m_restitution = 0.2f;
m_friction = 0.003f;
m_color = sf::Color(21,40,250);
m_name = "Light";

}

void Material::m_Floor()
{
    m_density = 2.0f;
    m_restitution = 0.00002f;
    m_friction = 0.6f;
    m_color = sf::Color(21,0,255);
    m_name = "Floor";
}

void Material::m_Rubber()
{
    m_density = 2.0f;
    m_restitution = .5f;
    m_friction = 0.3f;
    m_color = sf::Color(0,255,85);
    m_name = "Rubber";
}

void Material::m_Wood()
{
    m_density = 1.2f;
    m_restitution = 0.05f;
    m_friction = 0.8f;
    m_color = sf::Color(255,192,0);
    m_name = "Wood";
}

void Material::m_Ground_Img()
{
    m_density = 1.0f;
    m_restitution = 0.002f;
    m_friction = 0.3f;
    m_color = sf::Color(255,0,0);
    m_name = "Default";

    m_image = sf::Texture();
    m_image.Update(Resource::GetImage("image/ground-depth.png"));
    m_useImage=true;

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

std::string Material::GetName()
{
    return m_name;
}

sf::Texture* Material::GetImage()
{
    return &m_image;
}

sf::Text* Material::GetText()
{
    return &m_text;
}

sf::Font* Material::GetFont()
{
    return &m_font;
}
