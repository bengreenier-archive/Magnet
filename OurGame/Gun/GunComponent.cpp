#include "GunComponent.h"
#include <iostream>

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

/**********************************

    A helper function to create
    and return the components
    image as a sprite that can
    be drawn.

**********************************/
sf::Sprite GunComponent::GetSprite()
{
    std::cout<<GetImagePath()<<"\n";
    sf::Sprite Sprite;
    Sprite.SetImage(GetImage());
    Sprite.SetPosition(10,10);
    //GetImage()->GetWidth() the image width
    return Sprite;
}

/********************************

    Craft an image, and return
    it. use ImagePath to do so.

********************************/
sf::Image& GunComponent::GetImage()
{
       sf::Image Image;

    if (!Image.LoadFromFile(ImagePath))
    {
        std::cout<<"Failure To Load Image From: "<<ImagePath<<"\n";
    }

    return Image;
}
