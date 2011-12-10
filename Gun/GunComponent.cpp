#include "GunComponent.h"
#include "../ImageHandler.h"
#include <iostream>
#include <string>

/*********************************************************************

    The GunComponent Constructor, maps pieces to the component values,
    to allow this component to be a complete peice for later use
    to create a full fledged gun.

*********************************************************************/
GunComponent::GunComponent(int Damage,std::string Name,std::string ImagePath)
{

    GunComponent::ImagePath = ImagePath;
    GunComponent::Damage    = Damage;
    GunComponent::Name      = Name;
    GunComponent::Type      = TypeFinder();
    std::cout<<Type<<"\n";
    GunComponent::Length        = ImageHandler::GetImage(ImagePath).GetHeight();
    GunComponent::Width         = ImageHandler::GetImage(ImagePath).GetWidth();
    SetImage(ImageHandler::GetImage(ImagePath));


}

/**************************************

    A helper function to return the
    components imagepath at any time.

**************************************/
std::string GunComponent::GetImagePath()
{
    return GunComponent::ImagePath;
}

/****************************

    A helper function to
    return the components
    damage at any time.

****************************/
int GunComponent::GetDamage()
{
    return GunComponent::Damage;
}

/**********************************

    A helper function to return
    the components name at any
    time.

**********************************/
std::string GunComponent::GetName()
{
    return GunComponent::Name;
}

std::string GunComponent::GetType()
{
    return GunComponent::Type;
}


std::string GunComponent::TypeFinder()
{
     if (ImagePath.find("Assault")!=std::string::npos)
        return "Assault";
else if (ImagePath.find("Sniper")!=std::string::npos)
        return "Sniper";
else if (ImagePath.find("Smg")!=std::string::npos)
        return "Smg";
else if (ImagePath.find("Pistol")!=std::string::npos)
        return "Pistol";
else if (ImagePath.find("Launcher")!=std::string::npos)
        return "Launcher";
else if (ImagePath.find("Light Machine")!=std::string::npos)
        return "Light Machine";
else
        return "Invalid";
}
