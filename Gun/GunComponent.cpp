#include "GunComponent.h"
#include <iostream>
#include <string>

/*********************************************************************

    The GunComponent Constructor, maps pieces to the component values,
    to allow this component to be a complete peice for later use
    to create a full fledged gun.

*********************************************************************/
GunComponent::GunComponent()
{

}
GunComponent::~GunComponent()
{
    //delete [] m_sprite;
}

sf::Sprite* GunComponent::GetSpritePtr(){
    return &m_sprite;
}

/**************************************

    A helper function to return the
    components imagepath at any time.

**************************************/
std::string GunComponent::GetImagePath()
{
    return m_imagepath;
}

void GunComponent::SetImagePath(std::string path)
{
    m_imagepath = path;
    m_sprite.SetImage(ImageHandler::GetImage(m_imagepath));

    m_width = ImageHandler::GetImage(m_imagepath).GetWidth();
    m_height = ImageHandler::GetImage(m_imagepath).GetHeight();
}

int GunComponent::GetWidth()
{
    return m_width;
}

int GunComponent::GetHeight()
{
    return m_height;
}


std::string GunComponent::TypeFinder()
{
     if (m_imagepath.find("Assault")!=std::string::npos)
        return "Assault";
else if (m_imagepath.find("Sniper")!=std::string::npos)
        return "Sniper";
else if (m_imagepath.find("Smg")!=std::string::npos)
        return "Smg";
else if (m_imagepath.find("Pistol")!=std::string::npos)
        return "Pistol";
else if (m_imagepath.find("Launcher")!=std::string::npos)
        return "Launcher";
else if (m_imagepath.find("Light Machine")!=std::string::npos)
        return "Light Machine";
else
        return "Invalid";
}
