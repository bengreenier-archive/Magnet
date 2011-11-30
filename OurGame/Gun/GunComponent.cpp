#include "GunComponent.h"

/*********************************************************************

    The GunComponent Constructor, maps pieces to the component values,
    to allow this component to be a complete peice for later use
    to create a full fledged gun.

*********************************************************************/
GunComponent::GunComponent(sf::Image Image,int Damage,std::string Name)
{
    GunComponent::Image     = Image;
    GunComponent::Damage    = Damage;
    GunComponent::Name      = Name;

}

/*********************************

    A helper function to return
    the components image at any
    time.

*********************************/
sf::Image GunComponent::GetImage()
{
    return GunComponent::Image;
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
