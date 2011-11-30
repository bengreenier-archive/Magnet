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
    GunComponent::ScaleFactor   = .3f;

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

    The way this is being done,
    with arguments, is invalid.
    i should be looking into
    setting the .SetPosition
    in GunMaker, as GunMaker
    knows the dimensions to
    all GunComponents in use.

**********************************/
sf::Sprite GunComponent::GetSprite(std::string Position,int x,int y)
{
    //std::cout<<GetImagePath()<<"\n";
    Sprite.SetImage(Image);

    if (Position == "Rear")
        Sprite.SetPosition(x,y);
    else if (Position == "Middle")
        Sprite.SetPosition(x+(Width*ScaleFactor),y);
    else if (Position == "Front")
        Sprite.SetPosition(x+(Width*ScaleFactor)+(Width*ScaleFactor),y);
    else
        std::cout<<"Invalid GetSprite(STRING) given.\n";

    Sprite.SetScale(ScaleFactor,ScaleFactor);

    return Sprite;
}
