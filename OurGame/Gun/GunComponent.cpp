#include "GunComponent.h"
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
    if (!Image.LoadFromFile(ImagePath))
    {
        std::cout<<"Failure To Load Image From: "<<ImagePath<<"\n";
    }
    GunComponent::Length        = Image.GetHeight();
    GunComponent::Width         = Image.GetWidth();
    Sprite.SetImage(Image);


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

