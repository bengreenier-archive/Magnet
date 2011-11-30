#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include <SFML/Graphics.hpp>
#include <string>
class GunComponent
{
    public:
        GunComponent(int Damage,std::string Name,std::string ImagePath);          // Default Constructor, take the parts needed to make a component


        int         GetDamage();                        // Return the components damge value
        std::string GetName();                          // Return the components name
        sf::Sprite  GetSprite();                        // Return a drawable sprite made from Image
        std::string GetImagePath();                     // Return the components image path
        sf::Image& GetImage();                           // Craft and return the an image from the components image path

    protected:
    private:

        int         Damage;                             // Store The damage value for the component here
        std::string Name;                               // Store The name value for the component here
        std::string ImagePath;                          // Store ImagePath here

};

#endif // GUNCOMPONENT_H
