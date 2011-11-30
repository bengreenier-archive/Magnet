#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include <SFML/Graphics.hpp>
#include <string>
class GunComponent
{
    public:
        GunComponent(sf::Image Image,int Damage,std::string Name);                     // Default Constructor, take the parts needed to make a component

        sf::Image   GetImage();                         // Return the components image
        int         GetDamage();                        // Return the components damge value
        std::string GetName();                          // Return the components name

    protected:
    private:
        sf::Image   Image;                              // Store The image for the component here
        int         Damage;                             // Store The damage value for the component here
        std::string Name;                               // Store The name value for the component here

};

#endif // GUNCOMPONENT_H
